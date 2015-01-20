#include "fader.h"

//--------------------------------------------------------------
Fader::Fader(){
    setup();
}

//--------------------------------------------------------------
void Fader::setup(){
    curtain.allocate(1920, 1080, GL_RGBA);
    curtain.begin();
    ofClear(255,255,255, 0);
    curtain.end();
    overlap = 10;
    
    fadAlpha = 0.0;
    fadSpeed = 1.5;
    
    fade = STAY;
    delay = 0;
}

//--------------------------------------------------------------
void Fader::update(){
    switch (fade) {
        case UP:
            if (delay > 0) {
                delay--;
            } else {
                delay = 0;
                if (fadAlpha < 255) {
                    fadAlpha += fadSpeed;
                } else {
                    fadAlpha = 255;
                    fade = STAY;
                    ofNotifyEvent(curtainDrawn, fadAlpha);
                    //cout << "notified event UP" << endl;
                }
            }
            
            break;
            
        case DOWN:
            if (delay > 0) {
                delay--;
            } else {
                delay = 0;
                if (fadAlpha > 0) {
                    fadAlpha -= fadSpeed;
                } else {
                    fadAlpha = 0;
                    fade = STAY;
                    ofNotifyEvent(curtainDrawn, fadAlpha);
                    //cout << "notified event DOWN" << endl;
                }
            }
            
            break;
            
        default:
            break;
    }
    
    fadAlpha = ofClamp(fadAlpha, 0, 255);
    if (delay != 0) {
        //cout << delay << endl;
    }
    drawCurtain();
//    cout << fadAlpha << endl;

}

//--------------------------------------------------------------
void Fader::drawCurtain(){
    curtain.begin();
    ofSetColor(0, 0, 0,fadAlpha);
    ofRect(0,0, curtain.getWidth(), curtain.getHeight());
    ofSetColor(255, 255, 255,255);
    curtain.end();
//    cout << fadAlpha << endl;
}



//--------------------------------------------------------------
void Fader::draw(){
    draw(ofGetWidth(),ofGetHeight());
    
}

//--------------------------------------------------------------
void Fader::draw(float w, float h){
    ofPushMatrix();
    ofTranslate(0, 0, 10);
    curtain.draw(-overlap,-overlap,w+overlap,h+overlap);
    ofPopMatrix();
}

//--------------------------------------------------------------
void Fader::fadeUp(){
    fade = UP;
}

//--------------------------------------------------------------
void Fader::fadeDown(){
    fade = DOWN;
}

//--------------------------------------------------------------
void Fader::blackout(){
    fadAlpha = 255;
    fade = STAY;
}

//--------------------------------------------------------------
float Fader::getAlpha(){
    return fadAlpha;
}

//--------------------------------------------------------------
bool Fader::getisFullyCovered(){
    if (fadAlpha >= 255) {
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void Fader::setSpeed(float f) {
    fadSpeed = f;
}

//--------------------------------------------------------------
void Fader::setAlpha(float f) {
    fadAlpha = f;
    fade = STAY;
}

//--------------------------------------------------------------
void Fader::addDelay(int d) {
    if (d < 0) {
        delay = abs(d);
        fadeDown();
    } else if (d > 0) {
        delay = abs(d);
        fadeUp();
    }
}

//--------------------------------------------------------------
void Fader::clearDelay() {
    delay = 0;
}


