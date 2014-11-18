#include "button.h"

ofEvent<string> Button::buttonClickedGlobal = ofEvent<string>();

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
        ofRegisterMouseEvents(this);
        bRegisteredEvents = true;
    }
    activeCol.set(255);
    inactiveCol.set(128);
    buttonCol = inactiveCol;
    pos = ofVec2f(0,0);
    buttWidth = 0.0;
    toggleSize = 20;
    
    if (bText == "xx") {
        isToggle = true;
        active = true;
        //cout << "set toggle and true" << endl;
    } else {
        isToggle = false;
        active = false;
    }
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
        string s;
        if (isToggle) {
            active = !active;
            //cout << active << endl;
            if (active) {
                s = "eegOn";
            } else {
                s = "eegOff";
            }
        } else {
            s = buttText;
        }
        ofNotifyEvent(buttonClickedGlobal, s);
        //cout << buttText << endl;
    }
}

//--------------------------------------------------------------
bool Button::inside(float _x, float _y ){
    ofRectangle rect;
    if (!isToggle) {
        rect = font.getStringBoundingBox(buttText, 0,0);
    } else {
        rect = ofRectangle(0, 0, toggleSize, toggleSize);
    }
    if (_x >= pos.x && _x <= pos.x + rect.width && _y >= pos.y - rect.height && _y <= pos.y) {
        return true;
    } else {
        return false;
    }
}

//--------------------------------------------------------------
void Button::updatePos(float x, float y){
    if (isToggle) {
        pos = ofVec2f(x+5,y+3);
    } else {
        pos = ofVec2f(x,y);
    }
    
    buttWidth = font.stringWidth(buttText);
}

//--------------------------------------------------------------
float Button::width(){
    return buttWidth;
}

//--------------------------------------------------------------
void Button::draw(float x, float y, int alpha){
    updatePos(x, y);
    ofSetColor(buttonCol.r,buttonCol.g,buttonCol.b,alpha);
    if (isToggle) {
        if (active) {
            ofSetColor(0,alpha);
            ofLine(pos.x+2, pos.y-2, pos.x+(toggleSize-2), pos.y-(toggleSize-2));
            ofLine(pos.x+2, pos.y-(toggleSize-2), pos.x+(toggleSize-2), pos.y-2);
            //ofCircle(pos.x, pos.y, 4* toggleSize);
            
        }
        ofSetColor(buttonCol.r,buttonCol.g,buttonCol.b,alpha);
        ofRect(pos.x, pos.y, toggleSize, -toggleSize);
    } else {
        font.drawString(buttText, pos.x, pos.y);
    }
    ofSetColor(255,alpha);
}