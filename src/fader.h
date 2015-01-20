#pragma once
#include "ofMain.h"

class Fader {
public:
    Fader();
    
    void setup();
    void update();
    void draw();
    void draw(float w, float h);
    
    void fadeUp();
    void fadeDown();
    bool getisFullyCovered();
    float getAlpha();
    void blackout();
    void setSpeed(float f);
    void setAlpha(float f);
    void addDelay(int d);
    void clearDelay();
    
    ofEvent<float> curtainDrawn;
    
protected:
    int delay;
    void drawCurtain();
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