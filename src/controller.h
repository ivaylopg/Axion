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
        void exit();
    
    const float VERSION = 0.2;
    
    bool helpOn;
    bool debugMessages;
    
    State current_state;
    State next_state;
    
    Vid current_video;
    Fader fader;
    Intro introPlayer;
    MoviePlayer player;
    Tunnel tunnel;
    SoundPlayer sound;
    Outro outroPlayer;
};
