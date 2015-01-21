#pragma once
#include "ofMain.h"
#include "eegVisLine.h"

#include "messenger.h"


class EEGVis : public Messenger {
    
public:
    EEGVis();
    void setup();
    void update();
    void update(bool connected);
    void updateValues(vector<float> v);
    void draw();
    void draw(float w, float h);

private:
    void drawCanvas();
    
    ofFbo canvas;
    
    vector<float> mapped;
    vector<visLine> visLines;
//    bool checkDead( visLine &v )
};