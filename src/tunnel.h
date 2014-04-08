#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxFPSCamera.h"

class Tunnel {
public:
    Tunnel();
    
    void setup();
    void update();
    void draw(float alph = 0);
    
    bool initialized = false;
    
    ofxAssimpModelLoader hallModel;
    ofMesh hallMesh;
    ofLight hallLight;
    float mOffset;
    float offRange;
    float meshAdvance;
    
    ofxFPSCamera camera;
    bool camTargSet;
    ofVec3f camPos;
    
    ofVec3f goal1;
    ofVec3f goal2;
};