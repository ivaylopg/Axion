
#include "moviePlayer.h"

//--------------------------------------------------------------
MoviePlayer::MoviePlayer(){
	setup();
}

// Do something with closeMovie() ?

//--------------------------------------------------------------
void MoviePlayer::setup(){
    if(initialized) {
		return;
	}

	initialized = true;
    isDone = false;
    
    whichMov = 0;
    
    for (int i = 0; i < N_VIDEOS; i++) {
        ofVideoPlayer* p = new ofVideoPlayer();
        videos.push_back(p);
        videos.at(i)->loadMovie("mov/" + ofToString(i) + ".mp4");
        videos.at(i)->setLoopState(OF_LOOP_NONE);
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
void MoviePlayer::update(){
    if (videos.at(whichMov)->getIsMovieDone()) {
        videos.at(whichMov)->stop();
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



