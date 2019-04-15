#pragma once

#include "ofMain.h"
#include "ofxKinectForWindows2.h"
#include "ofxOsc.h"
#include <iostream>
#include <fstream>

constexpr int PORTIN = 2320;
constexpr int PORTEX = 2323;
constexpr int BUFFERLIMIT = 3;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void getKinectData();
		void getOsc();
		void sendFrame(string addr, vector<float> frame);
		void saveData();
		void debugData();

		// OSC
		constexpr string REMOTE = "10.17.69.43";
		//string REMOTE = "127.0.0.1";
		ofxOscReceiver osc_receiver;
		ofxOscSender osc_sender;
		
		// KINECT 
		ofxKFW2::Device kin;
		vector< vector<float> > kinData;

		// GRAPHICS
		ofShader bandShader;
		ofFbo debugFbo;
		ofVec2f focus[3];

		// STATE VARIABLES
		bool streamData, showDebug, kinColor;
		bool tracking;
		int trackId;
		float trackBuffer;
};