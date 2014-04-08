#pragma once
#include "ofMain.h"

class Fader {
public:
    Fader();
    
    void setup();
    void update();
    void draw();
    void moveOn();
    void fadeUp();
    bool fullCover();
    
    bool initialized = false;
    float speed;
    float holdTime;         // in seconds
    
    void drawTest();
    float getAlpha();
    
protected:
    float fadFac;
    float fadz;
    float fadAlpha;
    bool movingOn;
    bool revealing;
    bool fullyCovered;
    bool isFading;
    
};