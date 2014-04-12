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
    
    if (!hasStarted && volume < 0.65) {
        volume+=0.005;
    } else {
        hasStarted = true;
        volume = 0.65;
    }
    
    sound1.setVolume(volume);
    
}


//--------------------------------------------------------------
void SoundPlayer::play(){
    if (!sound1.getIsPlaying()) {
        sound1.play();
    }

}

//--------------------------------------------------------------
void SoundPlayer::newVolume(float f){
    volume = f;
}




