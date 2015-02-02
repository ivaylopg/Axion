#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxFPSCamera.h"

class Iss {
public:
    Iss();
    
    void setup();
    void update();
    void draw();
    void pause(bool b);
    
private:
    bool isPaused;
};