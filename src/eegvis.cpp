#include "eegvis.h"

EEGvis::EEGvis(){
    oldValLine = 0;
    newValLine = 0;
    oldValWedge = 0;
    newValWedge = 0;
    drawLine = true;
    drawWedge = false;
    started = false;
    //update(newVal);
}

//--------------------------------------------------------------
void EEGvis::update(float _newVal){
    if (_newVal > -100) {
        if (!started) {
            started = true;
        }
        oldValLine = newValLine;
        newValLine = ofMap(_newVal, -3, 3, -ofGetHeight()/2, ofGetHeight()/2, true);
    }
    if (started) {
        line.setParameters(1, ease, ofxTween::easeInOut, oldValLine, newValLine, 1000, 0);
    }
}

//--------------------------------------------------------------
void EEGvis::draw(){
    
    if (drawLine) {
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, 0, 1);
        if (started) {
            ofSetColor(90,255);
            /*
            float tweenVal = line.update();
            if (tweenVal >= 0) {
                ofRect(0, -1, tweenVal, 8);
            } else {
                ofRect(tweenVal, -1, tweenVal, 8);
            }
            */
            ofRect(0, -1, line.update(), 8);
            //cout << "update: " << line.update() << endl;
        }
        ofSetColor(200);
        glLineWidth(3);
        ofLine(0, 0, 0, 15);
        glLineWidth(1);
        ofSetColor(255);
        ofPopMatrix();
    }
}