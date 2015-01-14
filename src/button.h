#pragma once
#include "ofMain.h"

class Button {
public:
    Button();
    ~Button();
    void setup(ofTrueTypeFont *f, string bText);
    void draw(float x, float y, int alpha = 255);
    void updatePos(float x, float y);
    float width();
    
    bool inside(float _x, float _y );
    
    void mouseMoved(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    
    static ofEvent<string> buttonClickedGlobal;
    
private:
    string buttText;
    ofImage buttImg;
    ofTrueTypeFont	font;
    ofColor activeCol;
    ofColor inactiveCol;
    ofColor buttonCol;
    ofVec2f pos;
    float buttWidth;
    bool isToggle;
    bool active;
    int toggleSize;
    
protected:
    bool bRegisteredEvents;
};
