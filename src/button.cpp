#include "button.h"

//--------------------------------------------------------------
Button::Button(){
}

//--------------------------------------------------------------
Button::~Button(){
    if(bRegisteredEvents) {
        ofUnregisterMouseEvents(this); // disable litening to mous events.
        bRegisteredEvents = false;
    }
}

//--------------------------------------------------------------
void Button::setup(ofTrueTypeFont *f, string bText){
    font = *f;
    buttText = bText;
    //inside = false;
    if(!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
        bRegisteredEvents = true;
    }
    activeCol.set(255);
    inactiveCol.set(128);
    buttonCol = inactiveCol;
    pos = ofVec2f(0,0);
}

//--------------------------------------------------------------
void Button::mouseMoved(ofMouseEventArgs & args){
    if (inside(args.x, args.y)) {
        buttonCol = activeCol;
    } else {
        buttonCol = inactiveCol;
    }
}

//--------------------------------------------------------------
void Button::mouseDragged(ofMouseEventArgs & args){}

//--------------------------------------------------------------
void Button::mousePressed(ofMouseEventArgs & args){}

//--------------------------------------------------------------
void Button::mouseReleased(ofMouseEventArgs & args){
    if (inside(args.x, args.y)) {
    }
}

//--------------------------------------------------------------
bool Button::inside(float _x, float _y ){
    ofRectangle rect = font.getStringBoundingBox(buttText, 0,0);
    if (_x >= pos.x && _x <= pos.x + rect.width && _y >= pos.y - rect.height && _y <= pos.y) {
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void Button::updatePos(float x, float y){
    pos = ofVec2f(x,y);
}

//--------------------------------------------------------------
void Button::draw(float x, float y){
    updatePos(x, y);
    ofSetColor(buttonCol);
    font.drawString(buttText, pos.x, pos.y);
    ofSetColor(255);
}