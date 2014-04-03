#include "intro.h"


//--------------------------------------------------------------
Intro::Intro(){
	setup();
}

//--------------------------------------------------------------
void Intro::setup(){
    if(initialized) {
		return;
	}
    
	initialized = true;
    
    introImg.loadImage("logo.png");
    introModel.loadModel("introMesh.obj");
    introModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
}


//--------------------------------------------------------------
void Intro::update(){
    introModel.update();
    introMesh = introModel.getCurrentAnimatedMesh(0);
    introModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
}

//--------------------------------------------------------------
void Intro::draw(){
    float scl = (float) ofGetWidth() / (float) ofGetScreenWidth();
    
	//ofBackgroundGradient(ofColor(20,20,20),ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/6);
    //ofScale(.6, .6);
    ofScale(scl*0.6, scl*0.6);
    ofTranslate(-introImg.width/2, 0);
    introImg.draw(0, 0);
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
    
}