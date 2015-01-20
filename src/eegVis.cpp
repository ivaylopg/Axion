#include "eegVis.h"

EEGVis::EEGVis(){
    setup();
}

//--------------------------------------------------------------
void EEGVis::setup() {
    interpolationType = msa::kInterpolationCubic;
    useLength = false;
    spline2D.reserve(8);
    numSteps = 8 * 4;
    
    canvas.allocate(1920, 1080, GL_RGBA);
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
    drawCanvas();
}

//--------------------------------------------------------------
void EEGVis::updateValues(vector<float> v) {
    mapped.clear();
    mapped = v;
    
    for (int i = 0; i < 10; i++) {
        cout << mapped[i] << ", ";
    }
    cout << endl;
}

//--------------------------------------------------------------
void EEGVis::drawCanvas() {
    canvas.begin();
    ofBackground(100);
    ofSetColor(255);
    
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