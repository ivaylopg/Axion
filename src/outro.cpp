#include "outro.h"


//--------------------------------------------------------------
Outro::Outro(){
	setup();
}


//--------------------------------------------------------------
void Outro::setup(){
    if(initialized) {
		return;
	}
    
	initialized = true;
    
    outImage.loadImage("logo.png");
}


//--------------------------------------------------------------
void Outro::update(){
}

//--------------------------------------------------------------
void Outro::draw(){
    float scl = (float) ofGetWidth() / (float) ofGetScreenWidth();
    ofBackground(0);
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/6);
    ofScale(scl*0.6, scl*0.6);
    ofTranslate(-outImage.width/2, 0);
    outImage.draw(0, 0);
    ofPopMatrix();
}