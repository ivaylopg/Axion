#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "button.h"
#include "ofEventUtils.h"
#include "ofEvents.h"


class Intro {
public:
    Intro();
    ~Intro();
    
    void setup();
    void update();
    void draw();
    
    void buttonPressed(string & e);
    
    Button startButton;
    Button settingsButton;
    Button quitButton;
    
    bool initialized = false;
    ofLight introLight;
    ofxAssimpModelLoader introModel;
    ofVec3f introPos;
    float introRot;
    
private:
    ofImage introImg;
    ofMesh introMesh;
    
    ofTrueTypeFont	akzidenz;
    ofTrueTypeFont	akzidenzB;
    
};