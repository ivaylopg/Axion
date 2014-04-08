#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include "ofxFPSCamera.h"

#include "intro.h"
#include "moviePlayer.h"
#include "tunnel.h"
#include "fader.h"


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
    
        enum State {
            A,
            B,
            C,
            D,
            Pause
        };
    
        enum Vid {
            m0,     // Martin intro
            m1,     // Martin 'doing things that cannot be done'
            m2,     // Martin 'artists can create another nature'
            m3,     // Martin 'envy of artists....i would kill science'
            m4,     // Martin 'people must talk to each other'
            m5,     // Martin no sound, long clip COLOR
            m6      // Martin 'we don't have a clue. No idea how to experiment'
        };
    
    Fader fader;
    
    State current_state;
    State next_state;
    
    ofxFPSCamera camera;
    bool camTargSet;
    
    Vid current_video;
    
    Intro introPlayer;
    MoviePlayer player;
    Tunnel tunnel;
};
