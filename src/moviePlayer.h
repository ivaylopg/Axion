#pragma once
#include "ofMain.h"

class MoviePlayer {
public:
    MoviePlayer();
    
    void setup(int howMany);
    void load(vector<string> s);
    void update();
    void draw(int x, int y);
    void draw(int x, int y, int w, int h);
    void play();
    void pause(bool b);
    void stop();
    void setFile(int i);
    void reset();
    void clear();
    bool isPlaying();
    string getPath();
    
    bool initialized = false;
    
    vector<ofVideoPlayer* > videos;
    int N_VIDEOS;
    int whichMov;
    
    bool isDone;
    bool loaded;
    bool isPaused;
    
};