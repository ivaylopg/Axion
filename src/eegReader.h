#pragma once
#include "ofMain.h"
#include "ofxThinkGear.h"
#include "MSAInterpolator.h"

class EEGreader {
public:
    EEGreader();
    
    void setup();
    void update();
    void draw();
    void free();
    void reset();
    bool hasNewInfo();
    void restart();
    void connect();
    bool getIsConnected();
    
    float diff10();
    float diff20();
    
    bool initialized = false;
    
    vector<ofVec2f> meds;
    vector<ofVec2f> atts;
    vector<float> attMedRatio;
    float ave3s;
    float ave10s;
    float ave20s;
    float diff10s;
    float diff20s;
    
    bool hasD20;
    bool hasD10;
    
    float result10s;
    float result20s;
    
    float values[10];
    float mapped[10];
    float averages[10];
    float loHi [10][2];
    int lastBlinkVal;
    int numBlinks;
    
    msa::Interpolator2D spline2D;
    msa::InterpolationType interpolationType;
    bool useLength;
    int numSteps;
    
    float getSignalQuality();
    
    ofEvent<float> pushedBack;
    
    
    
private:
    ofxThinkGear thinkGear;
    void blinkListener(float &param);
    float signalQuality;
    bool trying;
};