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
    
    current_state = Intro;
    next_state = Intro;
    
    display = ofVec4f(0,0,1920,1080);
    isPaused = false;

}

//--------------------------------------------------------------
void Axion::update(){
    
    checkAspect();
    
    switch (current_state) {
        case Intro:
            introPLayer.update();
            break;
            
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void Axion::draw(){
    ofBackground(0);
    
    //Adjusting for different aspect ratios:
    display = checkAspect();
    ofPushMatrix();
    ofTranslate(display.x, display.y);
    
    switch (current_state) {
        case Intro:
            introPLayer.draw(display.z,display.w);
            break;
            
        default:
            break;
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void Axion::keyPressed(int key){
    
}

//--------------------------------------------------------------
void Axion::keyReleased(int key){
    
}

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
void Axion::exit(){
//    ofLog(OF_LOG_NOTICE) << "##### QUITTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << " #####";
//    cout << "Axion is quitting..." << endl;
}