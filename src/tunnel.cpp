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
    
    distFactor = ((float)ofGetScreenWidth())/2560.0;
    
    goal1 = ofVec3f(442,0,854) * distFactor;
    goal2 = ofVec3f(-317,0,1175) * distFactor;
    
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
        if (camera.getPosition().squareDistance(goal1) < (4900.0 * distFactor)) {
//            ofSendMessage("SetVid:2");
//            ofSendMessage("NextState:3");
//            ofSendMessage("moveOn");
            ofSendMessage("TunnelA:1:3");
        }
        
        if (camera.getPosition().squareDistance(goal2) < (4900.0 * distFactor)) {
//            ofSendMessage("SetVid:1");
//            ofSendMessage("NextState:3");
//            ofSendMessage("moveOn");
            //ofSendMessage(" Where From : Which Branch : Next State ");
            ofSendMessage("TunnelA:2:3");
        }
    }
    
    if (secondTime) {
        if (camera.getPosition().squareDistance(goal1) < (250000.0 * distFactor) || camera.getPosition().squareDistance(goal2) < (250000.0 * distFactor)) {
//            ofSendMessage("SetVid:0");
//            ofSendMessage("NextState:7");
//            ofSendMessage("moveOn");
            //ofSendMessage(" Where From : Which Branch : Next State ");
            ofSendMessage("TunnelB:0:7");
        }
    }
    
    //hallMesh.drawFaces();
    hallMesh.drawWireframe();
    
    ofPopMatrix();
    
    hallLight.disable();
    ofDisableLighting();
    
    camera.end();
    
    /*
    ofDrawBitmapString("goal 1: " + ofToString(camera.getPosition().squareDistance(goal1)) + " | goal 2: " + ofToString(camera.getPosition().squareDistance(goal2)), 20,20);
    
    ofDrawBitmapString("Cam x: " + ofToString(camera.getPosition().x) + " | Cam y: " + ofToString(camera.getPosition().y) + " | Cam z: " + ofToString(camera.getPosition().z), 20,50);
    
    ofDrawBitmapString(ofToString(ofGetScreenWidth()) + "  |  " + ofToString(((float)(ofGetScreenWidth()/2560.0))), 20,80);
    */
}