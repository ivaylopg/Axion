#include "eegVisLine.h"

//--------------------------------------------------------------
visLine::visLine(){
    setup();
    
    mapped.clear();
    for (int i = 0; i < 10; i++) {
        //mapped.push_back(0.0);
        //mapped.push_back(ofRandom(100));
        
        //float f = (sin(i+5*TWO_PI+ofGetFrameNum()*2)+1)*20;
        float f = (sin(i+5+ofGetFrameNum()*2)+1)*20;
        f += ofRandom(-10, 10);
        mapped.push_back(f);
    }
    zValue = -8000;
    scl = 3;
    
    spline2D.clear();
    for (int i=0; i<10; i++) {
        int xval = 0;
        int yval = 0 + i * 216;
        ofVec2f v = ofVec2f(xval- mapped[i], yval );
        spline2D.push_back(v);
    }
    fade = true;
}

//--------------------------------------------------------------
visLine::visLine(vector<float> v){
    
    mapped.clear();
    mapped = v;
    zValue = -8000;
    scl = 3;
    
    spline2D.clear();
    for (int i=0; i<10; i++) {
        int xval = 0;
        int yval = 0 + i * 216;
        float mappedVal = mapped[i];
        if (mappedVal <= 0.5) {
            mappedVal = ofRandom(75);
        }
        if (mappedVal < 1) {
            mappedVal *=100;
        } else if (mappedVal < 10) {
            mappedVal *=10;
        } else if (mappedVal >=90) {
            mappedVal = ofRandom(80, 95);
        }
        ofVec2f v = ofVec2f(xval- mappedVal, yval );
        spline2D.push_back(v);
    }
    fade = true;
}

//--------------------------------------------------------------
void visLine::setup() {
    interpolationType = msa::kInterpolationCubic;
    useLength = false;
    spline2D.reserve(10);
    numSteps = 15;
    pos.clear();
    pos.reserve(numSteps);
    for (int i = 0; i < numSteps; i++) {
        pos.push_back(ofVec3f(0,0,0));
    }
    grey = 255;
}

//--------------------------------------------------------------
void visLine::update() {
    if (fade) {
        float grey = ofMap(zValue, -8000, -1000, 0, 255, true);
        ofSetColor(grey, 200);
    } else {
        ofSetColor(100,200);
    }
    zValue+=6;
}

//--------------------------------------------------------------
void visLine::draw() {
    draw(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void visLine::draw(float w, float h) {
    
    float xTrans = w/6;
    
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    glLineWidth(2);
    ofPushMatrix();
    ofTranslate(w/2, -h/2, zValue);
        ofPushMatrix();
        ofScale(scl, 1);
        ofTranslate(xTrans, 0);
        //ofLine(0, 0, 0, 2*h);
        drawInterpolatorSmooth(spline2D, numSteps,0,2);
        //drawInterpolatorRaw(spline2D,0,1);
        ofPopMatrix();
    
        ofScale(-scl, 1);
        ofTranslate(xTrans, 0);
        //ofLine(0, 0, 0, 2*h);
        drawInterpolatorSmooth(spline2D, numSteps,0,2);
        //drawInterpolatorRaw(spline2D,0,1);

    ofPopMatrix();
    glLineWidth(1);
    ofDisableAntiAliasing();
    ofDisableSmoothing();
}

//--------------------------------------------------------------
vector<ofVec3f> visLine::getSpline() {
    
    //pos.clear();
    float inc = 1.0f/numSteps;
    
    for (int i = 0; i < numSteps; i++) {
        float pct = (float) i+1.0f * (1.0f/numSteps);
        //pos[i] = ofVec3f(1,1,1);//spline2D.sampleAt(pct);
        pos[i] = spline2D.sampleAt(pct);
    }
    return pos;
}

//--------------------------------------------------------------
bool visLine::isDead() {
    if (zValue > 100) {
        return true;
    } else {
        return false;
    }
}