#include "ofMain.h"
#include "controller.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1366,768,OF_FULLSCREEN);			// <-------- setup the GL context
    //ofSetupOpenGL(1024,576,OF_FULLSCREEN);        // Different size of 16:9
	ofRunApp(new controller());
}
