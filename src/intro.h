#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "button.h"

class Intro {
public:
    Intro();
    ~Intro();
    
    void setup();
    void update();
    void draw();
    
    bool initialized = false;
    ofLight introLight;
    ofxAssimpModelLoader introModel;
    ofVec3f introPos;
    float introRot;
    
    Button startButton;
    
private:
    ofImage introImg;
    ofMesh introMesh;
    
    ofTrueTypeFont	akzidenz;
    ofTrueTypeFont	akzidenzB;
    
};