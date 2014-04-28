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
<<<<<<< HEAD
    
    bool initialized = false;
    
    bool isDone;
=======
    void newFile(string s);
    void fadeDown();
    void fadeUp();
    //bool fade(int which, float start, float stop);
    
    bool initialized = false;

>>>>>>> develop
    
    bool hasStarted;
    float volume;
    
    ofSoundPlayer sound1;
};