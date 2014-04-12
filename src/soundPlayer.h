#pragma once
#include "ofMain.h"

class SoundPlayer {
public:
    SoundPlayer();
    
    void setup();
    void update();
    void play();
    void pause();
    void newVolume(float f);
    
    bool initialized = false;
    
    bool isDone;
    
    bool hasStarted;
    float volume;
    
    ofSoundPlayer sound1;
};