#include "ofMain.h"
#include "controller.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1366,768,OF_FULLSCREEN);			// <-------- setup the GL context
    //ofSetupOpenGL(1024,576,OF_FULLSCREEN);        // Different size of 16:9
    
    ofSetDataPathRoot("../Resources/data/");        // If not building via the XCode Project on a Mac, you WILL need to comment this out!
                                                    // This is to make self-contained app (via xcode) on Mac, along with this run script:
                                                    // cp -r bin/data "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources";
    
	ofRunApp(new controller());
}
