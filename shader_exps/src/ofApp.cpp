#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();

    // shaders & graphics
    maskShader.load("shaders/shader.vert", "shaders/IC_band.frag");
    baseShader.load("shaders/shader.vert", "shaders/px_quascr_m.frag");
    fxShader.load("shaders/shader.vert", "shaders/IC_mirror.frag");

    camWidth  = ofGetWidth();
    camHeight = ofGetHeight();
    vidTex.allocate(camWidth, camHeight, GL_RGBA);
    fbo.allocate(camWidth, camHeight, GL_RGBA);
    fxFbo.allocate(camWidth, camHeight, GL_RGBA);

    select = false;

    // video camera
    vidGrab.setDeviceID(0);
    vidGrab.setDesiredFrameRate(30);
    vidGrab.initGrabber(camWidth, camHeight);
}

//--------------------------------------------------------------
void ofApp::update(){
    // camera update
    vidGrab.update();    
    if(vidGrab.isFrameNew()){
        vidTex = vidGrab.getTexture();
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255, 100);
    int w = ofGetWidth(); int h = ofGetHeight();
    ofVec2f cen = ofVec2f(w/2, h);
    ofVec2f pos = ofVec2f(mouseX, mouseY) - cen;
    float angle = -pos.angleRad(ofVec2f(0, 1));

    // base shader
    fbo.begin();
    ofClear(0, 0);
    baseShader.begin();
    baseShader.setUniform1f("u_time", ofGetElapsedTimef());
    baseShader.setUniform2f("u_resolution", w, h);
    baseShader.setUniform2f("u_position", cen.x, cen.y);
    baseShader.setUniform1f("u_angle", angle);
    ofDrawRectangle(0, 0, w, h);
    baseShader.end();
    fbo.end();
    ofTexture fboTex = fbo.getTexture();

    // // fx shader
    // fxFbo.begin();
    // ofClear(0, 0);
    // fxShader.begin();
    // fxShader.setUniformTexture("inTex", fboTex, 0);
    // fxShader.setUniform1f("u_time", ofGetElapsedTimef());
    // fxShader.setUniform2f("u_resolution", w, h);
    // fxShader.setUniform2f("u_position", mouseX, mouseY);
    // ofDrawRectangle(0, 0, w, h);
    // fxShader.end();
    // fxFbo.end();
    // ofTexture fxTex = fxFbo.getTexture();

    

    // mask shader
    if(select){ fbo.draw(0,0); }
    else {
        maskShader.begin();
        maskShader.setUniformTexture("inTex", fboTex, 0);
        // maskShader.setUniformTexture("inTex", fxTex, 0);
        // maskShader.setUniformTexture("inTex", vidTex, 0);
        maskShader.setUniform1f("u_time", ofGetElapsedTimef());
        maskShader.setUniform2f("u_resolution", w, h);
        maskShader.setUniform2f("u_position", mouseX, h-mouseY);
        maskShader.setUniform1f("u_angle", angle);
        maskShader.setUniform1f("u_speed", 5.);
        maskShader.setUniform1f("u_fade", 20.);
        ofDrawRectangle(0, 0, w, h);
        maskShader.end();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 's':
            select = !select; break;
        case 'a':
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