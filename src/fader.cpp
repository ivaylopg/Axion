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
    fadSpeed = 2.5;
    
    fade = STAY;
}

//--------------------------------------------------------------
void Fader::update(){
    switch (fade) {
        case UP:
            if (fadAlpha < 255) {
                fadAlpha += fadSpeed;
            } else {
                fadAlpha = 255;
                fade = STAY;
            }
            break;
            
        case DOWN:
            if (fadAlpha > 0) {
                fadAlpha -= fadSpeed;
            } else {
                fadAlpha = 0;
                fade = STAY;
            }
            break;
            
        default:
            break;
    }
    
    fadAlpha = ofClamp(fadAlpha, 0, 255);
    drawCurtain();
}

//--------------------------------------------------------------
void Fader::drawCurtain(){
    curtain.begin();
    ofSetColor(0, 0, 0,fadAlpha);
    ofRect(0,0, curtain.getWidth(), curtain.getHeight());
    ofSetColor(255, 255, 255,255);
    curtain.end();
    cout << fadAlpha << endl;
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



