#include "eegvis.h"

EEGvis::EEGvis(){
    oldValLine = 0;
    newValLine = 0;
    oldValWedge = 0;
    newValWedge = 0;
    drawLine = true;
    drawWedge = false;
    started = false;
    currState = 0;
    currVid = 99;
    takenBranch = 0;
    //update(newVal);
    
    for (int i = 0; i < 8; i++) {
        ofImage img;
        img.loadImage(ofToString(i)+".png");
        branches.push_back(img);
    }
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
void EEGvis::updateBranches(int state, string m) {
    currState = state;
    //cout << m << endl;
    for (int i = 0 ; i < 7; i++) {
        if (ofIsStringInString(m, ofToString(i))) {
            currVid = i;
            break;
        } else if (ofIsStringInString(m, "sec")) {
            currVid = 98;
        } else {
            currVid = 99;
        }
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
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()-150,50,1);
    //cout << currState << endl;
    if (currState == 1) {
        branches[0].draw(0,0, 150, 150);
    } else if (currState == 2) {
        if (currVid == 98){
            branches[takenBranch].draw(0,0, 150, 150);
        } else {
            branches[1].draw(0,0, 150, 150);
        }
    } else if (currState == 3) {
        if (currVid <= 4) {
            branches[1+currVid].draw(0,0, 150, 150);
            takenBranch = 1+currVid;
        }
    } else if (currState == 7){
        if (currVid == 5 || currVid == 6) {
            branches[1 + currVid].draw(0,0, 150, 150);;
        }
    }
    //cout << currVid << endl;
    ofPopMatrix();
    
}