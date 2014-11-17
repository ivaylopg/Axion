#pragma once
#include "ofMain.h"
#include "ofxTween.h"

class EEGvis {
    
public:
    EEGvis();
    
    void update(float _newVal);
    void draw();
    
    void toggleWedge();
    void toggleLine();
    
private:
    float oldValLine;
    float newValLine;
    float oldValWedge;
    float newValWedge;
    bool drawWedge;
    bool drawLine;
    
    ofxTween line;
    ofxTween wedge;
    ofxEasingLinear ease;
    
    vector<ofVec4f> oldWedges;
    bool started;
};