#include "intro.h"


//--------------------------------------------------------------
Intro::Intro(){
    setup();
}

Intro::~Intro(){
    //cout << "I'm dead" << endl;
}

//--------------------------------------------------------------
void Intro::setup(){
    if(initialized) {
        return;
    }
    firstTime = true;
    counter = 0;
    firstAlpha = 0;
    initialized = true;
    
    introImg.loadImage("logo.png");
    pointer.loadImage("pointer.png");
    introModel.loadModel("introMesh.obj");
    introModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    for (int i = 0; i < 4; i++) {
        ofImage img;
        img.loadImage("singal_" + ofToString(i) + ".png");
        mindwaveReception.push_back(img);
    }
    
    akzidenz.loadFont("akzidenz-grotesk-light.ttf", 16, true, true, true);
    akzidenzB.loadFont("akzidenz-grotesk-light.ttf", 26, true, true, true);
    akzidenzS.loadFont("akzidenz-grotesk-light.ttf", 14, true, true, true);
    startButton.setup(&akzidenzB, "BEGIN AXION");
    helpButton.setup(&akzidenz, "HELP");
    settingsButton.setup(&akzidenz, "xx");
    quitButton.setup(&akzidenz, "QUIT");
    restartButton.setup(&akzidenz, "RESTART");
    
    ofAddListener(Button::buttonClickedGlobal, this, &Intro::buttonPressed);
    
    showHelp = false;
    helpAlpha = 0;
    alphaStep = 5.0;
    
    useMindWave = true;
    pauseScreen = false;
}


//--------------------------------------------------------------
void Intro::buttonPressed(string &e){
    //cout << e << endl;
    if (e == "BEGIN AXION") {
        cout << "Begin Button" << endl;
        string s = "start";
        ofNotifyEvent(progControl, s);
    } else if (e == "HELP") {
        //cout << "Help Button" << endl;
        showHelp = !showHelp;
    } else if (e == "eegOn" || e == "eegOff") {
        //cout << e << endl;
        if (e == "eegOn") {
            useMindWave = true;
        } else {
            useMindWave = false;
        }
        ofNotifyEvent(progControl, e);
    } else if (e == "RESTART") {
        //cout << "Restart" << endl;
        ofNotifyEvent(progControl, e);
    } else if (e == "QUIT"){
        cout << "Quit Button" << endl;
        OF_EXIT_APP(0); 
    }
}

//--------------------------------------------------------------
void Intro::update(float eeg){
    introModel.update();
    introMesh = introModel.getCurrentAnimatedMesh(0);
    introModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    eegSignal = eeg;
}

//--------------------------------------------------------------
void Intro::draw(){
    ofSetColor(255);
    float scl = (float) ofGetWidth() / (float) ofGetScreenWidth();
    int imgW = (int) ceil(ofGetWidth()/4.5);
    int imgH = (int) ceil((imgW * introImg.height)/introImg.width);
    float transX = ofGetWidth()/6;
    float transY = ofGetHeight()/10;
    
    //ofBackgroundGradient(ofColor(20,20,20),ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    if (!pauseScreen) {
        ofPushMatrix();
        ofTranslate(transX, transY,-1);
        introImg.draw(0, 0, imgW, imgH);
        ofPopMatrix();
    }
    
    ofPushMatrix();
    ofTranslate(0,0,-1);
    if (pauseScreen) {
        float offset = 0.25;
        ofSetColor(255);
        akzidenzB.drawString("PAUSED", transX + imgW * 0.09, transY + imgH * offset);
        ofSetColor(128);
        akzidenz.drawString("PRESS ESCAPE KEY TO RESUME", transX + imgW * 0.09, transY + imgH * offset + 40);
        helpButton.draw(transX + imgW * 0.09, transY + imgH * offset + 80);
        ofSetColor(128);
        akzidenz.drawString("USE EEG:  ", transX + imgW * 0.09, transY + imgH * offset + 120);
        settingsButton.draw(transX + imgW * 0.09 + akzidenz.stringWidth("USE EEG:X"), transY + imgH * offset + 120);
        restartButton.draw(transX + imgW * 0.09, transY + imgH * offset + 160);
        quitButton.draw(transX + imgW * 0.09, transY + imgH * offset + 200);
    } else {
        if (counter < 6 * 60){
            counter ++;
        } else {
            if (firstAlpha < 255) {
                firstAlpha++;
            }
        }
        float offset = 1.25;
        
        float introAlph;
        if (firstTime) {
            introAlph = ofClamp(firstAlpha,0,255);
        } else {
            introAlph = 255;
        }
        startButton.draw(transX + imgW * 0.09, transY + imgH * offset, introAlph);
        helpButton.draw(transX + imgW * 0.09, transY + imgH * offset + 40, introAlph);
        ofSetColor(128, introAlph);
        akzidenz.drawString("USE EEG:  ", transX + imgW * 0.09, transY + imgH * offset + 80);
        settingsButton.draw(transX + imgW * 0.09 + akzidenz.stringWidth("USE EEG:X"), transY + imgH * offset + 80, introAlph);
        quitButton.draw(transX + imgW * 0.09, transY + imgH * offset + 120, introAlph);
    }
    ofPopMatrix();
    
    if (useMindWave) {
        ofPushMatrix();
        ofTranslate(0,0, -1);
        ofSetColor(200);
        //ofDrawBitmapString(ofToString(eegSignal), ofGetWidth()-50, 50);
        //mindwaveReception[0].draw(ofGetWidth()-100, 25, 75, 75/1.5749);
        if (eegSignal >= 200) {
            mindwaveReception[0].draw(ofGetWidth()-100, 25, 75, 75/1.5749);
        } else if (eegSignal >= 100) {
            mindwaveReception[1].draw(ofGetWidth()-100, 25, 75, 75/1.5749);
        } else if (eegSignal >= 1) {
            mindwaveReception[2].draw(ofGetWidth()-100, 25, 75, 75/1.5749);
        } else if (eegSignal == 0) {
            mindwaveReception[3].draw(ofGetWidth()-100, 25, 75, 75/1.5749);
        }
        ofSetColor(255,255);
        ofPopMatrix();
    }
//    1.5749
    if (showHelp) {
        if (helpAlpha < 255) {
            helpAlpha += alphaStep;
        }
        if (helpAlpha > 255) {
            helpAlpha = 255;
        }
    } else {
        if (helpAlpha > 0) {
            helpAlpha -= alphaStep;
        }
        if (helpAlpha < 0) {
            helpAlpha = 0;
        }
    }
    
    if (helpAlpha > 0) {
        ofPushMatrix();
        ofTranslate(0,0, -1);
        ofSetColor(128, helpAlpha);
        float resetLH = akzidenzS.getLineHeight();
        akzidenzS.setLineHeight(20);
        akzidenzS.drawString("Axion is an unconventional interactive documentary \nthat allows players to explore and discover for themselves", ofGetWidth()/2,ofGetHeight()/6);
        
        akzidenzS.drawString("Navigate using \"W\" to move FORWARD, \"S\" to move BACK, and \nLOOK around with the MOUSE.\n\nThe \"F\" key toggles Full Screen\nThe ESC key pauses the app", ofGetWidth()/2, ofGetHeight()/6 + 50);
        
        akzidenzS.setLineHeight(resetLH);
        ofSetColor(255,255);
        ofPopMatrix();
    }
    //ofSetColor(200);
    //ofCircle(ofGetMouseX(), ofGetMouseY(), 20);
    
    introLight.enable();
    ofSetColor(255, 255);
    
    ofPushMatrix();
    ofTranslate((ofGetWidth()/2)*0.3, (ofGetHeight()/2)*0.3, 300);
    ofTranslate(introModel.getPosition().x, introModel.getPosition().y, 0);
    
    ofRotateX(10);
    ofRotateZ(-20);
    ofRotateY(introRot);
    introRot+=0.05;
    
    ofTranslate(-introModel.getPosition().x, -introModel.getPosition().y, 0);
    
    ofxAssimpMeshHelper & meshHelper = introModel.getMeshHelper(0);
    ofMultMatrix(introModel.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    
    ofScale(scl, scl);
    //introMesh.drawFaces();
    introMesh.drawWireframe();
    
    ofPopMatrix();
    introLight.disable();
    ofDisableLighting();
    
    pointer.draw(ofGetMouseX(), ofGetMouseY(), 35, 35);
    
}

//--------------------------------------------------------------
void Intro::drawPaused() {
    pauseScreen = true;
    draw();
    pauseScreen = false;
    
}



