
#include "moviePlayer.h"

//--------------------------------------------------------------
MoviePlayer::MoviePlayer(){
}

// Do something with closeMovie() ?

//--------------------------------------------------------------
void MoviePlayer::setup(int howMany){
    
//    if(initialized) {
//		return;
//	}
//
//	initialized = true;
    isDone = false;
    N_VIDEOS = howMany;
    whichMov = 0;
    loaded = false;
    
    for (int i = 0; i < N_VIDEOS; i++) {
        ofVideoPlayer* p = new ofVideoPlayer();
        videos.push_back(p);
    }
}

//--------------------------------------------------------------
void MoviePlayer::load(vector<string> s) {
    if (!loaded) {
        for (int i = 0; i < s.size(); i++) {
            videos.at(i)->loadMovie(s[i]);
            videos.at(i)->setLoopState(OF_LOOP_NONE);
        }
        loaded = true;
    }
}

//--------------------------------------------------------------
void MoviePlayer::setFile(int i){
    videos.at(whichMov)->stop();
    videos.at(whichMov)->firstFrame();
    videos.at(i)->firstFrame();
    whichMov = i;
    isDone = false;
}

//--------------------------------------------------------------
void MoviePlayer::clear(){
    for (int i=0; i<videos.size(); i++) {
        videos.at(i)->stop();
        videos.at(i)->closeMovie();
    }
    //videos.clear();
}

//--------------------------------------------------------------
void MoviePlayer::update(){
    if (videos.at(whichMov)->getPosition() > 0.99) {
        videos.at(whichMov)->setPaused(true);
        isDone = true;
        return;
    } else {
        videos.at(whichMov)->update();
    }
}

//--------------------------------------------------------------
void MoviePlayer::draw(int x, int y){
    ofSetColor(255);
    if (!isDone) {
        videos.at(whichMov)->draw(x,y);
    }
}

//--------------------------------------------------------------
void MoviePlayer::draw(int x, int y, int w, int h){
    float ratio = 16/9;
    if (abs(ratio - (w/h)) > 0.01) {
        h = (w*9)/16;
    }
    
    if (!isDone) {
        videos.at(whichMov)->draw(x,y,w,h);
    }
}

//--------------------------------------------------------------
void MoviePlayer::play(){
    if (!isPlaying() && !isDone) {
        videos.at(whichMov)->play();
    }
}

//--------------------------------------------------------------
void MoviePlayer::pause(){
    videos.at(whichMov)->setPaused(true);
}

//--------------------------------------------------------------
void MoviePlayer::stop(){
    videos.at(whichMov)->stop();
}

//--------------------------------------------------------------
bool MoviePlayer::isPlaying(){
    return videos.at(whichMov)->isPlaying();
}

//--------------------------------------------------------------
void MoviePlayer::reset(){
    videos.at(whichMov)->firstFrame();
    isDone = false;
}

//--------------------------------------------------------------
string MoviePlayer::getPath(){
    string s = videos.at(whichMov)->getMoviePath();
    if (s.length() > 0) {
        return s;
    } else {
        s = " ";
        return s;
    }
}



