#pragma once
#include "ofMain.h"
#include "MSAInterpolator.h"

#include "messenger.h"


class EEGVis : public Messenger {
    
public:
    EEGVis();
    void setup();
    void update();
    void updateValues(vector<float> v);
    void draw();
    void draw(float w, float h);

private:
    void drawCanvas();
    msa::Interpolator2D spline2D;
    msa::InterpolationType interpolationType;
    bool useLength;
    int numSteps;
    
    ofFbo canvas;
    
    vector<float> mapped;
    
};