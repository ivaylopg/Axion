#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

class Outro {
public:
    Outro();
    
    void setup();
    void update();
    void draw();
    
    
    bool initialized = false;
    
    ofImage outImage;
<<<<<<< HEAD
=======
    ofTrueTypeFont	akzidenz32;
    ofTrueTypeFont	akzidenz28;
>>>>>>> develop
};