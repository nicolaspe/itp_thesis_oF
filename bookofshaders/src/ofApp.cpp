#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();

    shader[0].load("shaders/shader.vert", "shaders/09_grid.frag");
    shader[1].load("shaders/shader.vert", "shaders/07_varied.frag");
    shader[2].load("shaders/shader.vert", "shaders/07_morefunctions.frag");
    shader[3].load("shaders/shader.vert", "shaders/px_quascrystal.frag");
    shader[4].load("shaders/shader.vert", "shaders/px_smoke.frag");
    shader[5].load("shaders/shader.vert", "shaders/px_smokeCryst.frag");
    shader[6].load("shaders/shader.vert", "shaders/IC_lines.frag");
    shader[7].load("shaders/shader.vert", "shaders/IC_mirror.frag");

    shaderInd = 0;
    nowTex.allocate(640, 480, GL_RGBA);
    fbo.allocate(640, 480);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    int w = ofGetWidth();
    int h = ofGetHeight();

    shader[shaderInd].begin();
    shader[shaderInd].setUniform1f("u_time", ofGetElapsedTimef());
    shader[shaderInd].setUniform2f("u_resolution", w, h);
    shader[shaderInd].setUniform2f("u_position", mouseX, mouseY);
    ofDrawRectangle(0, 0, w, h);
    shader[shaderInd].end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case '0': shaderInd = 0; break;
        case '1': shaderInd = 1; break;
        case '2': shaderInd = 2; break;
        case '3': shaderInd = 3; break;
        case '4': shaderInd = 4; break;
        case '5': shaderInd = 5; break;
        case '6': shaderInd = 6; break;
        case '7': shaderInd = 7; break;
        default: break;
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