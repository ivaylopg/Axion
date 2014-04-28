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
<<<<<<< HEAD
=======
#include "eegReader.h"
>>>>>>> develop


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
<<<<<<< HEAD
=======
        void brancher(int source, int branch, int state);
>>>>>>> develop
        void exit();
    
    const float VERSION = 0.2;
    
    bool helpOn;
    bool debugMessages;
    
<<<<<<< HEAD
    State current_state;
    State next_state;
    
    Vid current_video;
    Fader fader;
    Intro introPlayer;
    MoviePlayer player;
    Tunnel tunnel;
    SoundPlayer sound;
    Outro outroPlayer;
=======
    float volume;
    
    State current_state;
    State next_state;
    
    EEGreader mind;
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
>>>>>>> develop
};
