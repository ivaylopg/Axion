#ifndef MoviePlayer_h
#define MoviePlayer_h

#include "ofMain.h"

class MoviePlayer {
public:
    MoviePlayer();
    
    void setup();
    void update();
    void draw(int x, int y);
    void draw(int x, int y, int w, int h);
    void play();
    void pause();
    void stop();
    void setFile(int i);
    void reset();
    bool isPlaying();
    
    bool initialized = false;
    
    vector<ofVideoPlayer* > videos;
    static const int N_VIDEOS = 7;
    int whichMov;
    
    bool isDone;
    
};
#endif