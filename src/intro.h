#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

class Intro {
public:
    Intro();
    ~Intro();
    
    void setup();
    void update();
    void draw();
    
    
    bool initialized = false;
    ofLight introLight;
    ofImage introImg;
    ofxAssimpModelLoader introModel;
    ofMesh introMesh;
    ofVec3f introPos;
    float introRot;
};