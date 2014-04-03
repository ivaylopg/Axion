#ifndef tunnel_h
#define tunnel_h

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"

class Tunnel {
public:
    Tunnel();
    
    void setup();
    void update();
    void draw();
    
    bool initialized = false;
    
    ofxAssimpModelLoader hallModel;
    
};
#endif