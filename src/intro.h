#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "fader.h"
#include "audioPlayer.h"

#include "messenger.h


class Intro : public Messenger {
public:
    Intro();
    ~Intro();
    void setup();
    void update();
    void draw();
    void draw(float w, float h);
    
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);

private:
    void drawCanvas();
    ofImage introImg;
    ofImage pointer;
    ofMesh introMesh;
//    bool initialized = false;
    int counter;
    
    ofFbo canvas;
    
    enum introStates {
        A,
        B,
        C
    };
    
    introStates introState;
    bool readyToMove;
    
    Fader introFader;
    void faderDone(float & f);
    
    AudioPlayer woodenBox;

    ofLight introLight;
    ofxAssimpModelLoader introModel;
    ofVec3f introPos;
    float introRot;
};