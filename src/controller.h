#pragma once

// addons
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxFPSCamera.h"

// classes
#include "states.h"
#include "intro.h"
#include "moviePlayer.h"
#include "tunnel.h"
#include "fader.h"
#include "soundPlayer.h"
#include "outro.h"
#include "eegReader.h"
#include "eegvis.h"

#include "ofEventUtils.h"
#include "ofEvents.h"


class controller : public ofBaseApp{

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
    
    const float VERSION = 0.39;
    
    bool helpOn;
    bool debugMessages;
    bool isPaused;
    
    float volume;
    
    ofFbo mainGraphics;
    
    State current_state;
    State next_state;
    
    EEGreader mind;
    EEGvis vis;
    bool usingEEG;
    Fader fader;
    SoundPlayer sound;
    
    Intro introPlayer;
    MoviePlayer playerIntro;
    Tunnel tunnel1;
    MoviePlayer playerBranch1;
    // EEG?
    MoviePlayer playerBranch2;
    //Tunnel tunnel2;
    MoviePlayer playerOutro;
    Outro outroPlayer;
    
    string lastMessage;
    
    vector<string> vids01;
    vector<string> vids02;
    vector<string> vids03;
    vector<string> vids04;
};
