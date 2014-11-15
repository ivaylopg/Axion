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
    
    initialized = true;
    
    introImg.loadImage("logo.png");
    pointer.loadImage("pointer.png");
    introModel.loadModel("introMesh.obj");
    introModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    akzidenz.loadFont("akzidenz-grotesk-light.ttf", 10, true, false, false, 0.3, 200);
    akzidenzB.loadFont("akzidenz-grotesk-light.ttf", 12, true, false, false, 0.3, 200);
    
    startButton.setup(&akzidenzB, "BEGIN AXION");
    settingsButton.setup(&akzidenz, "SETTINGS");
    quitButton.setup(&akzidenz, "QUIT");
    
    ofAddListener(Button::buttonClickedGlobal, this, &Intro::buttonPressed);
}


//--------------------------------------------------------------
void Intro::buttonPressed(string &e){
    //cout << e << endl;
    if (e == "BEGIN AXION") {
        cout << "Begin Button" << endl;
    } else if (e == "SETTINGS") {
        cout << "Settings Button" << endl;
    } else if (e == "QUIT"){
        cout << "Quit Button" << endl;
        OF_EXIT_APP(0); 
    }
}

//--------------------------------------------------------------
void Intro::update(){
    introModel.update();
    introMesh = introModel.getCurrentAnimatedMesh(0);
    introModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
}

//--------------------------------------------------------------
void Intro::draw(){
    ofSetColor(255);
    float scl = (float) ofGetWidth() / (float) ofGetScreenWidth();
    int imgW = (int) ceil(ofGetWidth()/4.5);
    int imgH = (int) ceil((imgW * introImg.height)/introImg.width);
    
    //ofBackgroundGradient(ofColor(20,20,20),ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    ofPushMatrix();
    float transX = ofGetWidth()/6;
    float transY = ofGetHeight()/10;
    ofTranslate(transX, transY,-20);
    //ofScale(.6, .6);
    //ofScale(scl*0.6, scl*0.6);
    //ofTranslate(-introImg.width/2, 0);
//    glPushAttrib(GL_ENABLE_BIT);
//    ofEnableAlphaBlending();
    introImg.draw(0, 0, imgW, imgH);
//    ofDisableAlphaBlending();
//    glPopAttrib();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0,0,-1);
    startButton.draw(transX + imgW * 0.09, transY + imgH * 1.25);
    settingsButton.draw(transX + imgW * 0.09, transY + imgH * 1.25 + 50);
    quitButton.draw(transX + imgW * 0.09, transY + imgH * 1.25 + 100);
    ofPopMatrix();
    
    
    introLight.enable();
    
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
    
    //ofSetColor(200);
    //ofCircle(ofGetMouseX(), ofGetMouseY(), 20);
    pointer.draw(ofGetMouseX(), ofGetMouseY(), 35, 35);
    
}