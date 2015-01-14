#include "soundPlayer.h"


//--------------------------------------------------------------
SoundPlayer::SoundPlayer(){
	setup();
}

//--------------------------------------------------------------
void SoundPlayer::setup(){
    if(initialized) {
		return;
	}
	initialized = true;
    
    hasStarted = false;
    volume = 0.0;
    
    sound1.loadSound("audio/1.aiff");
    
    
    sound1.setMultiPlay(false);
    sound1.setLoop(true);
}

//--------------------------------------------------------------
void SoundPlayer::update(){
    ofSoundUpdate();
    
    
//    if (!hasStarted && volume < 0.65) {
//        volume+=0.005;
//    } else {
//        hasStarted = true;
//        volume = 0.65;
//    }
    
    sound1.setVolume(volume);
    
}


//--------------------------------------------------------------
void SoundPlayer::play(){
    if (!sound1.getIsPlaying()) {
        sound1.play();
    }

}

//--------------------------------------------------------------
void SoundPlayer::pause(bool b){
    sound1.setPaused(b);

}

//--------------------------------------------------------------
void SoundPlayer::newVolume(float f){
    volume = f;
}

//--------------------------------------------------------------
void SoundPlayer::newFile(string s){
    sound1.setVolume(0);
    sound1.stop();
    sound1.unloadSound();
    sound1.loadSound(s);
    play();
}

//--------------------------------------------------------------
void SoundPlayer::fadeDown(){
    volume-=0.005;
}


//--------------------------------------------------------------
void SoundPlayer::fadeUp(){
    volume+=0.005;
}