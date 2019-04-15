#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;
	// settings.setSize(640, 480);
	settings.setSize(1280, 720);

	settings.setGLVersion(3, 3);
	ofCreateWindow(settings);

	ofRunApp( new ofApp() );
}
