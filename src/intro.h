#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxUI.h"

class Intro {
public:
    Intro();
    ~Intro();
    
    void setup();
    void update();
    void draw();
    
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    
    bool initialized = false;
    ofLight introLight;
    ofxAssimpModelLoader introModel;
    ofVec3f introPos;
    float introRot;
    
private:
    ofImage introImg;
    ofMesh introMesh;
};