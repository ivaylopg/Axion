#pragma once

// addons
#include "ofMain.h"
#include "ofEvents.h"


// classes
#include "messenger.h"
#include "states.h"
#include "intro.h"
#include "audioPlayer.h"
#include "eegReader.h"
#include "eegVis.h"


class Axion : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void drawHelp();
    void drawDebugMessages();
    void exit();
    
    const float VERSION = 0.5;
    
private:
    void messageListener(string & s);
    void volumeListener(float & f);
    void faderDone(float & f);
    void updateEegVis(vector<float> &v);
    ofVec4f checkAspect();
    
    ofVec4f display;
    bool isPaused;
    bool usingEEG;
    
    State current_state;
    State next_state;
    
    class Intro introPLayer;
    AudioPlayer backgroundSound;
    Fader mainFader;
    EEGReader mind;
    EEGVis mindVis;
    
    

};

/* BONEYARD

void mouseMoved(int x, int y );
void mouseDragged(int x, int y, int button);
void mousePressed(int x, int y, int button);
void mouseReleased(int x, int y, int button);
void windowResized(int w, int h);
void dragEvent(ofDragInfo dragInfo);
void gotMessage(ofMessage msg);
void gotMessage(ofMessage& msg);
void brancher(int source, int branch, int state);
void controlEvent(string & e);
void updateEegVis(float &f);

*/
