#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxFPSCamera.h"

class Iss {
public:
    Iss();
    
    void setup();
    void update();
    void draw();
    void pause(bool b);
    void resetCamera();
    
private:
    bool isPaused;
    int counter;
    ofSoundPlayer spaceSounds;
    bool playedOnce;
    
    bool showFR;
    ofxFPSCamera cam;
    ofVec3f labelPos;
    float labelHeight;
    
    ofSpherePrimitive starSphere;
    ofSpherePrimitive earthSphere;
    ofImage stars;
    ofImage earth;
    ofMaterial starsM;
    ofMaterial earthM;
    
    float eSpin;
    
    ofxAssimpModelLoader station;
    ofMesh stationMesh;
    
    ofxAssimpModelLoader ams;
    ofMesh amsMesh;
    ofLight	light;
    ofLight	light2;
    
    float distFactor;
};