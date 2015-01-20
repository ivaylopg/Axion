#pragma once
#include "ofMain.h"
#include "ofxThinkGear.h"
#include "messenger.h"

class EEGReader : public Messenger {
public:
    EEGReader();
    ~EEGReader();
    
    
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
    
    
    
    bool useLength;
    int numSteps;
    
    float getSignalQuality();
    ofEvent< vector<float> > pushedBack;
    
    
private:
    ofxThinkGear thinkGear;
    void setup();
    
    float signalQuality;
    bool trying;
    
    float values[10];
    float mapped[10];
    float averages[10];
    float loHi [10][2];
    vector<float> mappedVector;
};

/*
 ofEvent<float> pushedBack;
*/