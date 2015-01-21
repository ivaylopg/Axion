#include "eegVis.h"

EEGVis::EEGVis(){
    setup();
}

//--------------------------------------------------------------
void EEGVis::setup() {
    
    canvas.allocate(1920, 1080, GL_RGBA,4);
    canvas.begin();
    ofClear(255,255,255, 0);
    canvas.end();
    
    mapped.clear();
    for (int i = 0; i < 10; i++) {
        mapped.push_back(0.0);
    }
}

//--------------------------------------------------------------
void EEGVis::update() {
    update(false);
}

//--------------------------------------------------------------
bool checkDead( visLine &v ){
//    cout << "checking" << endl;
    return v.isDead();
}

//--------------------------------------------------------------
void EEGVis::update(bool connected) {
    if (ofGetFrameNum() % 60 == 0) {
        if (!connected) {
            visLines.push_back(visLine());
        }
        ofRemove(visLines,checkDead);
        //cout << visLines.size() << endl;
    }
    for (int i = 0; i < visLines.size(); i++) {
        visLines[i].update();
    }
    drawCanvas();
    
}

//--------------------------------------------------------------
void EEGVis::updateValues(vector<float> v) {
    mapped.clear();
    mapped = v;
    visLines.push_back(visLine(v));
    
    for (int i = 0; i < 10; i++) {
        //cout << mapped[i] << ", ";
    }
    //cout << endl;
}

//--------------------------------------------------------------
void EEGVis::drawCanvas() {
    canvas.begin();
    ofBackground(0);
    ofSetColor(255);
    
    for (int i = 0; i < visLines.size(); i++) {
        //visLines[i].draw(canvas.getWidth(), canvas.getHeight());
        vector<ofVec3f> splPoints = visLines[i].getSpline();
        ///*
        for (int j = 0; j < splPoints.size(); j++) {
            ofEllipse(splPoints[j].x, splPoints[j].y, splPoints[j].z, 10, 10);
            ;
        }
        //*/
    }
    
    canvas.end();
}

//--------------------------------------------------------------
void EEGVis::draw(){
    draw(ofGetWidth(),ofGetHeight());
    
}

//--------------------------------------------------------------
void EEGVis::draw(float w, float h){
    canvas.draw(0,0,w,h);
}

