#pragma once
#include "ofMain.h"

class Button {
public:
    Button();
    ~Button();
    void setup(ofTrueTypeFont *f, string bText);
    void draw(float x, float y);
    void updatePos(float x, float y);
    
    bool inside(float _x, float _y );
    
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    
    static ofEvent<float> buttonClickedGlobal;
    
private:
    string buttText;
    ofImage buttImg;
    ofTrueTypeFont	font;
    ofColor activeCol;
    ofColor inactiveCol;
    ofColor buttonCol;
    ofVec2f pos;
    
protected:
    bool bRegisteredEvents;
};
