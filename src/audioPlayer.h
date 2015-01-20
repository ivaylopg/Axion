#pragma once
#include "ofMain.h"

class AudioPlayer {
public:
    AudioPlayer();
    
    void setup();
    void setup(string s);
    void update();
    void play();
    void pause(bool b);
    void jumpToVolume(float f);
    void fadeToVolume(float f);
    void newFile(string s);
    void fadeOut();
    
    
private:
    float volume;
    float fadeSpeed;
    
    enum fading {
        UP,
        DOWN,
        OUT,
        STAY
    };
    
    fading fade;
    ofSoundPlayer sound1;
};