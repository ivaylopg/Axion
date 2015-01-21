#pragma once
#include "ofMain.h"
#include "MSAInterpolator.h"


class visLine {
    
public:
    visLine();
    void setup();
    void update();
    void draw();
    void draw(float w, float h);
    bool isDead();
    
private:
    msa::Interpolator2D spline2D;
    msa::InterpolationType interpolationType;
    bool useLength;
    int numSteps;
    
    vector<float> mapped;
    
};