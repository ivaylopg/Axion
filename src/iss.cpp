#include "iss.h"

//--------------------------------------------------------------
Iss::Iss(){
    setup();
}

//--------------------------------------------------------------
void Iss::setup() {
    isPaused = false;
    counter = 0;
}

//--------------------------------------------------------------
void Iss::update() {
    if (counter<60) {
        counter++;
    } else {
        ofSendMessage("TunnelB:0:7");
    }
}

//--------------------------------------------------------------
void Iss::draw() {
    ofSetColor(255, 0, 0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255);
}

//--------------------------------------------------------------
void Iss::pause(bool b) {
    isPaused = b;
}

//--------------------------------------------------------------
void Iss::resetCamera() {
    
}