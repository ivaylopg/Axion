#pragma once
#include "ofMain.h"

class Fader {
public:
    Fader();
    
    void setup();
    void update();
    void draw();
    
    bool initialized = false;
    
protected:
    float fadFac;
    float fadz;
    float fadAlpha;
    
};