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

}

//--------------------------------------------------------------
void Axion::update(){
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
    
    switch (current_state) {
        case Intro:
            introPLayer.draw();
            break;
            
        default:
            break;
    }
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
void Axion::exit(){
//    ofLog(OF_LOG_NOTICE) << "##### QUITTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << " #####";
//    cout << "Axion is quitting..." << endl;
}