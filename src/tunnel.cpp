#include "tunnel.h"

//--------------------------------------------------------------
Tunnel::Tunnel(){
	setup();
}

//--------------------------------------------------------------
void Tunnel::setup(){
    if(initialized) {
		return;
	}
    
	initialized = true;
    //hallModel.loadModel("Hallway1C.obj");
    hallModel.loadModel("hallway1.obj");
    hallModel.setPosition(0, 0, 0);
    offRange = 10;
    meshAdvance = 0;
    mOffset = 0;
}

//--------------------------------------------------------------
void Tunnel::update(){
    hallModel.update();
    hallMesh = hallModel.getCurrentAnimatedMesh(0);
    mOffset = ofMap(ofGetMouseX(), 0, ofGetWidth(), -offRange, offRange);
}

//--------------------------------------------------------------
void Tunnel::draw(){
	hallLight.enable();
    
    ofPushMatrix();
    ofSetColor(255);
    glLineWidth(1);
    
    
//    ofTranslate(hallModel.getPosition().x, hallModel.getPosition().y, 0);
//    ofScale(2.5, 2.5);
//    ofTranslate(-hallModel.getPosition().x, -hallModel.getPosition().y, 0);
    
    ofxAssimpMeshHelper & meshHelper = hallModel.getMeshHelper(0);
    ofMultMatrix(hallModel.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    
    //hallMesh.drawFaces();
    hallMesh.drawWireframe();

//
//    glLineWidth(4);
//    
//    ofSetColor(255, 0, 0);
//    ofLine(0, 0, -1000, 0, 0, 1000);
//    
//    ofSetColor(0,255,0);
//    ofLine(-1000, 0, 0, 1000, 0, 0);
//    
//    ofSetColor(0,0,255);
//    ofLine(0, -1000, 0, 0, 1000, 0);
    
    ofPopMatrix();
    
    hallLight.disable();
    ofDisableLighting();
}