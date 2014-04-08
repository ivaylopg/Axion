#include "fader.h"

//--------------------------------------------------------------
Fader::Fader(){
	setup();
}

//--------------------------------------------------------------
void Fader::setup(){
    if(initialized) {
		return;
	}
	initialized = true;
    
    fadFac = 0.77;
    fadAlpha = 0.0;
    //fadAlpha = 100.0;
    
    fadz = ofGetHeight() * fadFac;
    

}

//--------------------------------------------------------------
void Fader::update(){
    fadz = ofGetHeight() * fadFac;
}

//--------------------------------------------------------------
void Fader::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, fadz);
    ofSetColor(255,0,0, fadAlpha);
    ofRect(-ofGetWidth()/2, -ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    
    ofSetColor(255, 255);
    ofDrawBitmapString(ofToString(fadz) + " : " + ofToString(ofGetWidth()) + " : " + ofToString(ofGetHeight()), 20, 20);
    
    
    ofPopMatrix();
    
    
}