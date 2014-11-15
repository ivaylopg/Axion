#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "button.h"
#include "ofEventUtils.h"
#include "ofEvents.h"


class Intro {
public:
    Intro();
    ~Intro();
    
    void setup();
    void update(float eeg);
    void draw();
    
    void buttonPressed(string & e);
    
    Button startButton;
    Button helpButton;
    Button settingsButton;
    Button quitButton;
    
    bool initialized = false;
    ofLight introLight;
    ofxAssimpModelLoader introModel;
    ofVec3f introPos;
    float introRot;
    
    ofEvent<string> progControl;
    
private:
    ofImage introImg;
    ofImage pointer;
    ofMesh introMesh;
    
    ofTrueTypeFont	akzidenz;
    ofTrueTypeFont	akzidenzB;
    
    float eegSignal;
    
    bool showHelp;
    float helpAlpha;
    
    bool useMindWave;
};