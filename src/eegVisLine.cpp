#include "eegVisLine.h"

//--------------------------------------------------------------
visLine::visLine(){
    interpolationType = msa::kInterpolationCubic;
    useLength = false;
    spline2D.reserve(8);
    numSteps = 8 * 4;
    
    mapped.clear();
    for (int i = 0; i < 10; i++) {
        mapped.push_back(0.0);
    }
    zValue = -8000;
    scl = 3;
}

//--------------------------------------------------------------
void visLine::update() {
}

//--------------------------------------------------------------
void visLine::draw() {
    draw(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void visLine::draw(float w, float h) {
    ofSetColor(255,255);
    
    ofPushMatrix();
    ofTranslate(w/2, -h/2, zValue);
        ofPushMatrix();
        ofScale(scl, 1);
        ofTranslate(w/6, 0);
        ofLine(0, 0, 0, 2*h);
        ofPopMatrix();
    
        ofScale(-scl, 1);
        ofTranslate(w/6, 0);
        ofLine(0, 0, 0, 2*h);

    ofPopMatrix();
    
    zValue+=6;
}

//--------------------------------------------------------------
bool visLine::isDead() {
    if (zValue > 100) {
        return true;
    } else {
        return false;
    }
}