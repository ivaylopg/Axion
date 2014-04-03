#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

class Tunnel {
public:
    Tunnel();
    
    void setup();
    void update();
    void draw();
    
    bool initialized = false;
    
    ofxAssimpModelLoader hallModel;
    ofMesh hallMesh;
    ofLight hallLight;
    float mOffset;
    float offRange;
    float meshAdvance;
    
};