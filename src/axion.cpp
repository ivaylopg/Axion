#include "axion.h"
#include "states.h"

//--------------------------------------------------------------
void Axion::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetEscapeQuitsApp(false);
        
#ifdef AXION_RELEASE
    cout << "You are in Release Mode!" << endl;
#elif AXION_DEBUG
    cout << "You are in Debug Mode!" << endl;
#endif
    
#ifdef __APPLE__
    CGDisplayHideCursor(NULL); // <- Sometimes necessary to hide cursor on Macs
#endif
    ofHideCursor();
    
    //ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    ofEnableSeparateSpecularLight();
    
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight()/2 - ofGetHeight()/2);
    
    //current_state = Intro;
    current_state = EEG_Vis;
    next_state = EEG_Vis;
    
    mind.reset();
    //mind.connect();
    usingEEG = false;
    
    display = ofVec4f(0,0,1920,1080);
    isPaused = false;
    
    backgroundSound.setup();
    backgroundSound.fadeToVolume(0.65);
    
    ofAddListener(mainFader.curtainDrawn, this, &Axion::faderDone);
    ofAddListener(mind.pushedBack, this, &Axion::updateEegVis);
    
    ofAddListener(Messenger::sendMessage , this, &Axion::messageListener);
    ofAddListener(Messenger::setVolume , this, &Axion::volumeListener);
}

//--------------------------------------------------------------
void Axion::update(){
    
    checkAspect();
    
    usingEEG = true;
    if (usingEEG) {
        mind.update();
    }
    
    switch (current_state) {
        case Intro:
            introPLayer.update();
            break;
            
        case EEG_Vis:
            if (usingEEG && mind.getIsConnected()) {
                mindVis.update(mind.hasNewInfo());
            } else {
                mindVis.update();
            }
            break;
            
        default:
            break;
    }
    
    backgroundSound.update();
    mainFader.update();
    
}

//--------------------------------------------------------------
void Axion::draw(){
    ofBackground(0);
    backgroundSound.play();
    
    //Adjusting for different aspect ratios:
    display = checkAspect();
    ofPushMatrix();
    ofTranslate(display.x, display.y);
    
    switch (current_state) {
        case Intro:
            introPLayer.draw(display.z,display.w);
            break;
            
        case EEG_Vis:
            mindVis.draw(display.z,display.w);
            break;
            
        default:
            break;
    }
    
    mainFader.draw(display.z, display.w);
    ofPopMatrix();
    
    drawDebugMessages();
}

//--------------------------------------------------------------
void Axion::keyPressed(int key){
    //mind.connect();
}

//--------------------------------------------------------------
void Axion::keyReleased(int key){
    
}


//--------------------------------------------------------------
ofVec4f Axion::checkAspect() {
    ofVec4f d;
    float ideal = 16/9;
    float curWidth = ofGetWidth();
    float curHeight = ofGetHeight();
    float curRatio = curWidth/curHeight;
    //cout << curRatio << endl;
    if (curRatio > 1.778) {
        d.x = 0;
        d.z = ofGetWidth();
        d.w = (d.z * 9)/16;
        d.y = (ofGetHeight()-d.w)/2;
    } else if(curRatio < 1.777){
        d.y = 0;
        d.w = ofGetHeight();
        d.z = (d.w * 16)/9;
        d.x = (ofGetWidth() - d.z)/2;
    } else {
        d = ofVec4f(0,0,ofGetWidth(),ofGetHeight());
    };
    return d;
}

//--------------------------------------------------------------
void Axion::messageListener(string &s){
    //cout << "move to something else!" << endl;
    //cout << s << endl;
    if (s == "next") {
        changeStates();
        }
}

//--------------------------------------------------------------
void Axion::volumeListener(float &f){
    float newVol = ofClamp(f, 0.0, 1.0);
    backgroundSound.fadeToVolume(newVol);
}

//--------------------------------------------------------------
void Axion::updateEegVis(vector<float> &v){
    //cout << "ping" << endl;
    mindVis.updateValues(v);
}

//--------------------------------------------------------------
void Axion::faderDone(float &f){
    //
}

//--------------------------------------------------------------
void Axion::changeStates(){
    switch (current_state) {
        case Intro:
            mainFader.blackout();
            current_state = next_state;
            next_state = EEG_Vis;
            mainFader.addDelay(-30);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void Axion::exit(){
    mind.free();
    
//    ofLog(OF_LOG_NOTICE) << "##### QUITTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << " #####";
    
    cout << "Axion is quitting..." << endl;
}

//--------------------------------------------------------------
void Axion::drawDebugMessages(){
    ofSetColor(255,0,0);
    switch (current_state) {
        default:
            if (true) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Mindwave Signal Quality: " + ofToString(mind.getSignalQuality()) + " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()),
                                   20,ofGetHeight() - 70);
            }
            break;
    }
}

/* BONEYARD

//--------------------------------------------------------------
void Axion::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Axion::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Axion::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Axion::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Axion::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Axion::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Axion::dragEvent(ofDragInfo dragInfo){

}


*/