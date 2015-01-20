#pragma once
#include "ofMain.h"

class Fader {
public:
    Fader();
    
    void setup();
    void update();
    void drawCurtain();
    void draw();
    void draw(float w, float h);
    
    void fadeUp();
    void fadeDown();
    bool getisFullyCovered();
    float getAlpha();
    void blackout();
    void setSpeed(float f);
    
protected:
    ofFbo curtain;
    float fadAlpha;
    float fadSpeed;
    float overlap;
    
    enum fading {
        UP,
        DOWN,
        STAY
    };
    
    fading fade;
};