#pragma once
#include "ofMain.h"

class MoviePlayer {
public:
    MoviePlayer();
    
<<<<<<< HEAD
    void setup();
=======
    void setup(int howMany);
    void load(vector<string> s);
>>>>>>> develop
    void update();
    void draw(int x, int y);
    void draw(int x, int y, int w, int h);
    void play();
    void pause();
    void stop();
    void setFile(int i);
    void reset();
<<<<<<< HEAD
=======
    void clear();
>>>>>>> develop
    bool isPlaying();
    string getPath();
    
    bool initialized = false;
    
    vector<ofVideoPlayer* > videos;
<<<<<<< HEAD
    static const int N_VIDEOS = 4;
    int whichMov;
    
    bool isDone;
=======
    int N_VIDEOS;
    int whichMov;
    
    bool isDone;
    bool loaded;
>>>>>>> develop
    
};