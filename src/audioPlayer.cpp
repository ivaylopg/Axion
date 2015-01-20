#include "audioPlayer.h"


//--------------------------------------------------------------
AudioPlayer::AudioPlayer(){
    //setup();
}

//--------------------------------------------------------------
void AudioPlayer::setup(){
    setup("audio/1.aiff");
}

//--------------------------------------------------------------
void AudioPlayer::setup(string s){
    volume = 0.0;
    fade = STAY;
    fadeSpeed = 0.005;
    sound1.loadSound(s);
    sound1.setMultiPlay(false);
    sound1.setLoop(true);
    sound1.setVolume(volume);
}

//--------------------------------------------------------------
void AudioPlayer::update(){
    ofSoundUpdate();
    float curVol = sound1.getVolume();
    
    switch (fade) {
        case UP:
            if (curVol < volume) {
                curVol+=fadeSpeed;
            } else {
                fade = STAY;
            }
            break;
            
        case DOWN:
            if (curVol > volume) {
                curVol-=fadeSpeed;
            } else {
                fade = STAY;
            }
            break;
            
        case OUT:
            if (curVol > 0) {
                curVol-=fadeSpeed;
            } else {
                fade = STAY;
            }
            break;
            
        default:
            break;
    }
    
    curVol = ofClamp(curVol, 0.0, 1.0);
    sound1.setVolume(curVol);
}


//--------------------------------------------------------------
void AudioPlayer::play(){
    if (!sound1.getIsPlaying()) {
        sound1.play();
    }
    
}

//--------------------------------------------------------------
void AudioPlayer::pause(bool b){
    sound1.setPaused(b);
    
}

//--------------------------------------------------------------
void AudioPlayer::jumpToVolume(float f){
    volume = f;
    sound1.setVolume(volume);
}

//--------------------------------------------------------------
void AudioPlayer::fadeToVolume(float f){
    float curVol = sound1.getVolume();
    volume = f;
    if (volume > curVol) {
        fade = UP;
    } else if (volume < curVol) {
        fade = DOWN;
    }
}

//--------------------------------------------------------------
void AudioPlayer::newFile(string s){
    sound1.setVolume(0);
    sound1.stop();
    sound1.unloadSound();
    sound1.loadSound(s);
    play();
}

//--------------------------------------------------------------
void AudioPlayer::fadeOut(){
    fade = OUT;
}

//--------------------------------------------------------------
bool AudioPlayer::getIsFaded(){
    //cout << sound1.getVolume() << endl;
    if (sound1.getVolume() == 0.0) {
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void AudioPlayer::stop(){
    sound1.stop();
}