#pragma once
#include "ofMain.h"
#include "MSAInterpolator.h"


class visLine {
    
public:
    visLine();
    visLine(vector<float> v);
    void setup();
    void update();
    void draw();
    void draw(float w, float h);
    bool isDead();
    vector<ofVec3f> getSpline();
    
private:
    msa::Interpolator2D spline2D;
    msa::InterpolationType interpolationType;
    bool useLength;
    int numSteps;
    
    vector<float> mapped;
    float zValue;
    float scl;
    bool fade;
    vector<ofVec3f> pos;
    float grey;
    
};