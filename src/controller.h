#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxFPSCamera.h"


#include "intro.h"
#include "moviePlayer.h"
#include "tunnel.h"
#include "fader.h"
#include "soundPlayer.h"


class controller : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        void gotMessage(ofMessage& msg);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawOut();
    
        enum State {
            A,      // Intro
            B,      // Movie Player
            C,      // Tunnel Player 1
            D,
            Pause
        };
    
    ///////////////////////////
    // Not using this yet...
        enum Vid {
            m0,     // Martin intro
            m1,     // Martin 'artists can create another nature...i would kill science''
            m2,     // Martin 'All reasons to beleive dark matter is real...'
            m3,     // Martin 'people must talk to each other'
            m4      // Martin 'It doesn't behave as if it was only the visible...'
        };
    ///////////////////////////
    
    ofImage outImage;
    
    Fader fader;
    
    State current_state;
    State next_state;
    
    //ofxFPSCamera camera;
    //bool camTargSet;
    
    Vid current_video;
    
    SoundPlayer sound = SoundPlayer();
    Intro introPlayer;
    MoviePlayer player;
    Tunnel tunnel;
};
