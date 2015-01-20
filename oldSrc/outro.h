#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "button.h"

class Outro {
public:
    Outro();
    
    void setup();
    void update();
    void draw();
    
    
    bool initialized = false;
    
    Button restartButton;
    
    ofImage outImage;
    ofImage pointer;
    ofTrueTypeFont	akzidenz32;
    ofTrueTypeFont	akzidenz28;
    ofTrueTypeFont	akzidenzS;
};