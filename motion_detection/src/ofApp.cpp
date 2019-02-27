#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(30);

	camWidth = 640;
	camHeight = 480;
	tolerance = 0.2;
	fade = 0.005;

	nowTex.allocate(camWidth, camHeight, GL_RGBA);
	preTex.allocate(camWidth, camHeight, GL_RGBA);
	fadeTex.allocate(camWidth, camHeight, GL_RGBA);
	fbo.allocate(camWidth, camHeight);

	//shader.load("shaders/shader.vert", "shaders/cam.frag");
	shader.load("shaders/shader.vert", "shaders/motion.frag");

	vidGrab.setDeviceID(0);
	vidGrab.setDesiredFrameRate(30);
	vidGrab.initGrabber(camWidth, camHeight);
}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrab.update();

	if (vidGrab.isFrameNew()) {
		nowTex = vidGrab.getTexture();

		fbo.begin();
		ofClear(0, 0);
		shader.begin();
		shader.setUniformTexture("nowTex", nowTex, 0);
		shader.setUniformTexture("preTex", preTex, 1);
		shader.setUniformTexture("targetTex", fadeTex, 2);
		shader.setUniform1f("tolerance", tolerance);
		shader.setUniform1f("fade", fade);
		//shader.setUniform1f("u_time", ofGetElapsedTimef());
		//shader.setUniform2f("u_resolution", camWidth, camHeight);
		ofDrawRectangle(0, 0, camWidth, camHeight);
		shader.end();
		fbo.end();

		fadeTex = fbo.getTexture();
		
		ofPixels pix;
		nowTex.readToPixels(pix);
		preTex.loadData(pix);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	fadeTex.draw(0, 0);
	//nowTex.draw(640, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
