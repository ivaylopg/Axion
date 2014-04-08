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
    
    camera.setup();
    camTargSet = false;
    //camera.speed =  0.8f;
    camera.speed =  1.0f;
    camera.sensitivityX = 0.05f;
    camera.sensitivityY = 0.05f;
    camera.accel = 0.05f;
    camera.disableMove();
    camera.disableStrafe();
    
    camPos = ofVec3f(0,0,0);
    
    goal1 = ofVec3f(442,0,854);
    goal2 = ofVec3f(-317,0,1175);
    
    secondTime = false;
}

//--------------------------------------------------------------
void Tunnel::update(){
    hallModel.update();
    hallMesh = hallModel.getCurrentAnimatedMesh(0);
    mOffset = ofMap(ofGetMouseX(), 0, ofGetWidth(), -offRange, offRange);
}

//--------------------------------------------------------------
void Tunnel::draw(float alph){
    camera.enableMove();
    camera.begin();
    if (!camTargSet) {
        camera.target(ofVec3f(0,0,1));
        camTargSet = true;
    }
    
    camPos = camera.getPosition();
	hallLight.enable();
    
    ofPushMatrix();
    ofSetColor(255,255-alph);
    glLineWidth(1);
    
    ofxAssimpMeshHelper & meshHelper = hallModel.getMeshHelper(0);
    ofMultMatrix(hallModel.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);

    //cout << "Cam x: " << camera.getPosition().x << " | Cam y: " << camera.getPosition().y << " | Cam z: " << camera.getPosition().z << endl;
    
    //cout << "goal 1: " << camera.getPosition().distance(goal1) << " | goal 2: " << camera.getPosition().distance(goal2) << endl;
    
    /*
    if (camPos.z < -52.0) {
        camPos.z = -52.0;
        camera.clip(camPos);
    }
    */
    
    if (!secondTime) {
        if (camera.getPosition().distance(goal1) < 70) {
            ofSendMessage("SetVid:1");
            ofSendMessage("NextState:1");
            ofSendMessage("moveOn");
        }
        
        if (camera.getPosition().distance(goal2) < 70) {
            ofSendMessage("SetVid:2");
            ofSendMessage("NextState:1");
            ofSendMessage("moveOn");
        }
    }
    
    if (secondTime) {
        if (camera.getPosition().distance(goal1) < 500 || camera.getPosition().distance(goal2) < 500) {
            ofSendMessage("SetVid:3");
            ofSendMessage("NextState:1");
            ofSendMessage("moveOn");
        }
    }
    
    
    
    
    //hallMesh.drawFaces();
    hallMesh.drawWireframe();
    
    ofPopMatrix();
    
    hallLight.disable();
    ofDisableLighting();
    
    camera.end();
}