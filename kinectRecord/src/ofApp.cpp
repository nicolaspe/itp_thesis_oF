#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	kin.open();
	kin.initColorSource();
	kin.initBodySource();
	kin.initBodyIndexSource();

	recording = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	kin.update();
	recordKinectData();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255);
	ofSetColor(255);
	
	// Color is at 1920x1080 instead of 512x424 so we should fix aspect ratio
	float colorHeight = 640 * (kin.getColorSource()->getHeight() / kin.getColorSource()->getWidth());
	float colorTop = (640 - colorHeight) / 2.0;
	kin.getColorSource()->draw(0, 0, 640, 360);

	kin.getBodyIndexSource()->draw(0, 360, 640, 480);
	kin.getBodySource()->drawProjected(0, 360, 640, 480, ofxKFW2::ProjectionCoordinates::DepthCamera);

	ofColor col(255, 0, 0);
	if (recording) { col = ofColor(0, 255, 0); }
	ofSetColor(col);
	ofDrawCircle(740, 50, 20);
}


//--------------------------------------------------------------
void ofApp::recordKinectData() {
	auto bodies = kin.getBodySource()->getBodies();
	for (auto body : bodies) {
		// only keep going if the body is being tracked
		if (body.tracked && recording) {
			vector<float> jointData;

			int id = body.bodyId;
			jointData.push_back(id);
			float ellapsed = ofGetElapsedTimeMicros() / 1000.;
			jointData.push_back(ellapsed);

			for (auto joint : body.joints) {
				ofVec3f pos = joint.second.getPosition();
				ofVec4f rot = joint.second.getOrientation().asVec4();
				jointData.push_back(pos.x);
				jointData.push_back(pos.y);
				jointData.push_back(pos.z);
				jointData.push_back(rot.x);
				jointData.push_back(rot.y);
				jointData.push_back(rot.z);
				jointData.push_back(rot.w);
			}

			kinData.push_back(jointData);
		}
	}
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 's':	// [S]AVE DATA
		saveData();
		kinData.clear();
		ofResetElapsedTimeCounter();
		break;
	case 'r':	// [R]ECORD DATA
		recording = !recording;
		break;
	case 'f':	// [F]LUSH DATA
		kinData.clear();
		ofResetElapsedTimeCounter();
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
