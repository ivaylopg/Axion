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
    
    fadFac = 0.775;
    fadAlpha = 0.0;
    //fadAlpha = 100.0;
    
    fadz = ofGetHeight() * fadFac;
    fullyCovered = false;
    movingOn = false;
    revealing = false;
    speed = 3;
    holdTime = 1.0;
    
    isFading = false;
    
    //ofRegisterGetMessages(this);

}

//--------------------------------------------------------------
void Fader::update(){
    fadz = ofGetHeight() * fadFac;
    
    if (movingOn && !revealing) {
        if (fadAlpha >= 255) {
            fullyCovered = true;
        }
        if (fadAlpha < (255 + (holdTime * ofGetFrameRate() * speed)) ) {
            
            fadAlpha+=speed;
        } else {
            revealing = true;
            fadAlpha = 255;
        }
    }
    if (movingOn && revealing) {
        if (fadAlpha > 0) {
            fadAlpha-=speed;
        }
    }
}

//--------------------------------------------------------------
void Fader::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, fadz);
    ofSetColor(0, ofClamp(fadAlpha,0,255));
    ofRect(-ofGetWidth()/2, -ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    ofPopMatrix();
    
    if (movingOn && fullyCovered && revealing && fadAlpha <= 0) {
        fadAlpha = 0;
        movingOn = false;
        revealing = false;
        fullyCovered = false;
        isFading = false;
    }
}

//--------------------------------------------------------------
void Fader::drawTest(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, fadz);
    ofSetColor(0, 255);
    ofRect(-ofGetWidth()/2, -ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    ofPopMatrix();
    
    ofSetColor(255, 255);
    ofDrawBitmapString(ofToString(fadz+1) + " : " + ofToString(ofGetWidth()) + " : " + ofToString(ofGetHeight()), 20, 20);
}

//--------------------------------------------------------------
void Fader::moveOn(){
    if (!isFading) {
        isFading = true;
        movingOn = true;
    }
}

////--------------------------------------------------------------
//void Fader::gotMessage(ofMessage& msg){
//    /*
//    const char * a = "moveOn";
//    const char * b = "fadeUp";
//    std::strncmp(a, b, 6);
//    */
//    
//    if (ofIsStringInString("moveOn", msg.message)) {
//        cout << msg.message << endl;
//    }
//    
//}

//--------------------------------------------------------------
float Fader::getAlpha(){
    return ofClamp(fadAlpha, 0, 255);
}

//--------------------------------------------------------------
void Fader::fadeUp(){
    if (!isFading) {
        isFading = true;
        movingOn = true;
        fadAlpha = 255;
        revealing = true;
        fullyCovered = true;
    }
}

//--------------------------------------------------------------
bool Fader::fullCover(){
    return fullyCovered;
}