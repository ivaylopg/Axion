#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "fader.h"


class Intro {
public:
    Intro();
    ~Intro();
    void setup();
    void update();
    void drawCanvas();
    void draw();
    void draw(float w, float h);
    
    
    ofLight introLight;
    ofxAssimpModelLoader introModel;
    ofVec3f introPos;
    float introRot;
    
    ofEvent<string> progControl;
    
    bool firstTime;
    int counter;
    int firstAlpha;

private:
    ofImage introImg;
    ofImage pointer;
    ofMesh introMesh;
    bool initialized = false;
    
    ofFbo canvas;
    
    enum introStates {
        A,
        B,
        C
    };
    
    introStates introState;
};