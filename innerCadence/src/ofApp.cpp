#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// KinectForWindows2 setup
	kin.open();
	kin.initColorSource();
	kin.initBodySource();
	kin.initBodyIndexSource();

	// graphics setup
	bandShader.load("shaders/shader.vert", "shaders/IC_simple.frag");
	debugFbo.allocate(ofGetWidth(), ofGetHeight());
	for(size_t i=0; i<focus.size; i++){ focus[i] = ofVec2f(0, 0); }

	// state variables init
	streamData = false;
	showDebug = true;
	kinColor = false;
	tracking = false;
	tracked_id = -1;
	trackBuffer = 0.;

	// OSC setup
	osc_receiver.setup(PORTIN);
	osc_sender.setup(REMOTE, PORTEX);
}

//--------------------------------------------------------------
void ofApp::update(){
	kin.update();
	getKinectData();

	getOsc();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(220);
	int w = ofGetWidth();
	int h = ofGetHeight();

	// debug kinect fbo
	debugFbo.begin();
	debugFbo.clear();
	ofSetColor(255);
	if(kinColor){ 
		kin.getColorSource()->draw(0, 0, w, h); 
	} else {
		kin.getBodyIndexSource()->draw(0, 0, w, h);
		kin.getBodySource()->drawProjected(0, 0, w, h, ofxKFW2::ProjectionCoordinates::DepthCamera);
	}	
	debugFbo.end();

	// bandShader.begin();
	// bandShader.setUniform2f("u_resolution", w, h);
	// bandShader.setUniformTexture("inTex", debugFbo.getTexture(), 0);
	// bandShader.setUniform2f("u_position", focus[0].x, focus[0].y);
	// ofDrawRectangle(0, 0, w, h);
	// bandShader.end();

	// debug data
	if(showDebug){ debugData(); }

}

//--------------------------------------------------------------
void ofApp::getKinectData() {
	// variable for buffering, keeps track if any body is tracked
	bool trackLoop = false;
	// get delta time
	float elapsed = ofGetElapsedTimeMicros() / 1000.;

	auto bodies = kin.getBodySource()->getBodies();
	for (auto body : bodies) {
		// only keep going if the body is being tracked
		if (body.tracked) {
			trackLoop = true;	// if there's any body being tracked

			// check for id and tracking state before continuing
			int id = body.bodyId;
			if(!tracking){ break; }
			else if(id >= 0 && id != trackId){ break; }
			else if(id < 0){ trackId = id; }

			vector<float> jointData;
			vector<float> quatData;

			jointData.push_back(id);
			jointData.push_back(elapsed); quatData.push_back(elapsed);
			// check joints
			for (auto joint : body.joints) {
				ofVec3f pos = joint.second.getPosition();
				jointData.push_back(pos.x);
				jointData.push_back(pos.y);
				jointData.push_back(pos.z);
				ofVec4f rot = joint.second.getOrientation().asVec4();
				jointData.push_back(rot.x); quatData.push_back(rot.x);
				jointData.push_back(rot.y); quatData.push_back(rot.y);
				jointData.push_back(rot.z); quatData.push_back(rot.z);
				jointData.push_back(rot.w); quatData.push_back(rot.w);
				switch(joint.first){
					case 0: // spine base 
						focus[0] = joint.second.getPositionInDepthMap();
						break;
					case 6:  // hand left
						focus[1] = joint.second.getPositionInDepthMap();
						break;
					case 10: // hand right
						focus[2] = joint.second.getPositionInDepthMap();
						break;
				}
			}

			kinData.push_back(jointData);
			if (streamData) { sendFrame("/qframe", quatData); }
		}
	}
	// add and check the buffer
	int mult = trackLoop ? 1 : -1;
	trackBuffer = ofClamp(trackBuffer +mult*elapsed, 0, BUFFERLIMIT+1);
	if(trackBuffer >= BUFFERLIMIT && !tracking){
		tracking = true;
		trackId = -1;
	} else if(trackBuffer <= 1 && tracking){
		tracking = false;
		trackId = -1;
	}
}


//--------------------------------------------------------------
void ofApp::getOsc() {
	while (osc_receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		osc_receiver.getNextMessage(m);

		ofLog() << "new message @ : " << m.getAddress();

		string addr = m.getAddress();
		if (addr == "/result/length") {

		} else if(addr == "/control/stream") {
			streamData = m.getArgAsBool(0);
		} else if(addr == "/control/capture") {
			bool val = m.getArgAsBool(0);			
		} else if(addr == "/control/save") {
			bool val = m.getArgAsBool(0);
			if(val){
				saveData();
				kinData.clear();
				ofResetElapsedTimeCounter();
			}
		} else if(addr == "/control/flush") {
			bool val = m.getArgAsBool(0);
			if(val){
				kinData.clear();
				ofResetElapsedTimeCounter();
			}
		} 
	}
}

void ofApp::sendFrame(string addr, vector<float> frame) {
	ofxOscMessage msg;
	msg.setAddress(addr);
	// add values
	for (size_t i = 0; i < frame.size(); i++) {
		msg.addFloatArg(frame[i]);
	}
	osc_sender.sendMessage(msg);
}


//--------------------------------------------------------------
void ofApp::saveData() {
	std::ofstream dataFile;
	std::string filename = "data_" + std::to_string(ofGetUnixTime()) + ".tsv";

	dataFile.open(filename);
	// create header
	dataFile << "id" << '\t';
	dataFile << "timestamp" << '\t';
	for (size_t i = 0; i < 25; i++)
	{
		dataFile << 'j' << i << '_' << "px" << '\t';
		dataFile << 'j' << i << '_' << "py" << '\t';
		dataFile << 'j' << i << '_' << "pz" << '\t';
		dataFile << 'j' << i << '_' << "rx" << '\t';
		dataFile << 'j' << i << '_' << "ry" << '\t';
		dataFile << 'j' << i << '_' << "rz" << '\t';
		dataFile << 'j' << i << '_' << "rw" << '\t';
	}
	dataFile << endl;
	// add data!
	for (size_t i = 0; i < kinData.size(); i++)
	{
		vector<float> frame = kinData[i];
		for (size_t j = 0; j < frame.size(); j++)
		{
			dataFile << frame[j] << '\t';
		}
		dataFile << endl;
	}
	dataFile.close();
	ofLog() << "data saved in: " << filename << endl;
}

void ofApp::debugData() {
	// draw texture from Kinect
	debugFbo.draw(0,0);
	// draw text zone
	ofSetColor(180, 120);
	ofDrawRectangle(5, 5, 55, 205);
	// data stream indicator
	if(streamData){ ofSetColor(0,255,0); ofDrawCircle(10, 10, 10); }
	// draw text with info
	ofSetColor(0);
	string info = "timestamp: " + std::to_string(ofGetElapsedTimeMillis()) + '\n';
	info += "\n== TRACKING INFO ==\n";
	info += "tracking: " + std::to_string(tracking) + '\n';
	info += "track id: " + std::to_string(trackId)  + '\n';
	info += "track buffer: " + std::to_string(trackBuffer) + '\n';
	info += "\n== FOCUS POINTS ==\n";
	info += "spine base: " + std::to_string(focus[0]) + '\n';
	info += "hand left: "  + std::to_string(focus[1]) + '\n';
	info += "hand right: " + std::to_string(focus[2]) + '\n';
	ofDrawBitmapString(info, 10, 30);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case 'd':	// SHOW [D]EBUG INFO
			showKinect = !showKinect;
			break;
		case 's':	// [S]TREAM DATA
			streamData = !streamData;
			break;
		case 'v':	// DATA SA[V]E
			saveData();
			kinData.clear();
			ofResetElapsedTimeCounter();
			break;
		case 'f':	// [F]LUSH DATA
			kinData.clear();
			ofResetElapsedTimeCounter();
			break;
		
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){ }