#include "ofMain.h"
#include "controller.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1366,768,OF_FULLSCREEN);			// <-------- setup the GL context
    //ofSetupOpenGL(1024,576,OF_FULLSCREEN);        // Different size of 16:9
    
    
#ifdef OF_RELEASE                                   // If not building via the XCode Project on a Mac, you WILL need to comment this out!
    ofSetDataPathRoot("../Resources/data/");        // This is to make self-contained app (via xcode) on Mac, along with this run script:
#endif                                              // cp -r bin/data "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources";
    
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofLogToFile("Axion_Log.txt", true);
    //ofLogToConsole();
	ofRunApp(new controller());
}
