#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	
	settings.setGLVersion(3, 3);
	//settings.setSize(1920, 1080);
	//settings.windowMode = OF_FULLSCREEN;

	settings.setSize(640, 360);
	ofCreateWindow(settings);
	
	ofRunApp(new ofApp());
}
