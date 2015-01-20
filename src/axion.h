#pragma once

// addons
#include "ofMain.h"


// classes
#include "states.h"
#include "intro.h"


class Axion : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void gotMessage(ofMessage& msg);
    void drawHelp();
    void drawDebugMessages();
    void brancher(int source, int branch, int state);
    void controlEvent(string & e);
    void updateEegVis(float &f);
    void exit();
    
    const float VERSION = 0.5;
    
private:
    State current_state;
    State next_state;
    
    class Intro introPLayer;
};
