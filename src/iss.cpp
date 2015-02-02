#include "iss.h"

//--------------------------------------------------------------
Iss::Iss(){
    setup();
}

//--------------------------------------------------------------
void Iss::setup() {
    isPaused = false;
    counter = 0;
    
    spaceSounds.loadSound("audio/2b.aiff");
    
    spaceSounds.setMultiPlay(false);
    spaceSounds.setLoop(false);
//    spaceSounds.setPan(-1.0f);
    spaceSounds.setVolume(1.0);
//    spaceSounds.play();
    playedOnce = false;
}

//--------------------------------------------------------------
void Iss::update() {
    if (spaceSounds.getPosition() == 1.0) {
        ofSendMessage("TunnelB:0:7");
    }
    
    if (!spaceSounds.getIsPlaying() && !playedOnce) {
        spaceSounds.play();
    } else if (spaceSounds.getIsPlaying()){
        playedOnce = true;
    }
    
    
    
//    if (counter<180) {
//        counter++;
//    } else {
//        ofSendMessage("TunnelB:0:7");
//    }
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
    playedOnce = false;
    spaceSounds.setPosition(0.0);
    
    
}