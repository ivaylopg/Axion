#include "tunnel.h"

//--------------------------------------------------------------
Tunnel::Tunnel(){
	setup();
}

//--------------------------------------------------------------
void Tunnel::setup(){
    hallModel.loadModel("Hallway1C.obj");
    hallModel.setPosition(ofGetWidth()/2, ofGetHeight()/2 , 100);
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
    ofTranslate(0,0,meshAdvance);
    meshAdvance+=0.25;
    ofTranslate(hallModel.getPosition().x, hallModel.getPosition().y, 0);
    ofScale(2.5, 2.5);
    ofTranslate(mOffset, 0, 0);
    ofTranslate(-hallModel.getPosition().x, -hallModel.getPosition().y, 0);
    
    ofxAssimpMeshHelper & meshHelper = hallModel.getMeshHelper(0);
    ofMultMatrix(hallModel.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);
    
    //hallMesh.drawFaces();
    hallMesh.drawWireframe();
    
    ofPopMatrix();
    
    hallLight.disable();
    ofDisableLighting();
}