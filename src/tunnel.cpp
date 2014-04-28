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
<<<<<<< HEAD
    offRange = 10;
    meshAdvance = 0;
    mOffset = 0;
=======
>>>>>>> develop
    
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
    
<<<<<<< HEAD
=======
    hallModel.update();
    hallMesh = hallModel.getCurrentAnimatedMesh(0);
    
>>>>>>> develop
    secondTime = false;
}

//--------------------------------------------------------------
void Tunnel::update(){
<<<<<<< HEAD
    hallModel.update();
    hallMesh = hallModel.getCurrentAnimatedMesh(0);
    mOffset = ofMap(ofGetMouseX(), 0, ofGetWidth(), -offRange, offRange);
=======
    //hallModel.update();
    //hallMesh = hallModel.getCurrentAnimatedMesh(0);
>>>>>>> develop
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
<<<<<<< HEAD
=======

    if (!secondTime) {
        hallLight.setPosition(camera.getPosition());
        float attenuationFactor = 0.008 * (2560.0/ofGetScreenWidth());
        hallLight.setAttenuation(0,attenuationFactor,0);
    } else {
        hallLight.setPosition(0,0,0);
        hallLight.setAttenuation(1,0,0);
    }
>>>>>>> develop
    
    ofPushMatrix();
    ofSetColor(255,255-alph);
    glLineWidth(1);
    
    ofxAssimpMeshHelper & meshHelper = hallModel.getMeshHelper(0);
    ofMultMatrix(hallModel.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);

<<<<<<< HEAD
    //cout << "Cam x: " << camera.getPosition().x << " | Cam y: " << camera.getPosition().y << " | Cam z: " << camera.getPosition().z << endl;
    
    //cout << "goal 1: " << camera.getPosition().distance(goal1) << " | goal 2: " << camera.getPosition().distance(goal2) << endl;
    
=======

>>>>>>> develop
    /*
    if (camPos.z < -52.0) {
        camPos.z = -52.0;
        camera.clip(camPos);
    }
    */
<<<<<<< HEAD
    if (!secondTime) {
        if (camera.getPosition().squareDistance(goal1) < (4900.0 * distFactor)) {
            ofSendMessage("SetVid:1");
            ofSendMessage("NextState:1");
            ofSendMessage("moveOn");
        }
        
        if (camera.getPosition().squareDistance(goal2) < (4900.0 * distFactor)) {
            ofSendMessage("SetVid:2");
            ofSendMessage("NextState:1");
            ofSendMessage("moveOn");
=======
    
    if (!secondTime) {
        if (camera.getPosition().squareDistance(goal1) < (4900.0 * distFactor)) {
            ofSendMessage("TunnelA:0:3");
        }
        
        if (camera.getPosition().squareDistance(goal2) < (4900.0 * distFactor)) {
            ofSendMessage("TunnelA:2:3");
>>>>>>> develop
        }
    }
    
    if (secondTime) {
        if (camera.getPosition().squareDistance(goal1) < (250000.0 * distFactor) || camera.getPosition().squareDistance(goal2) < (250000.0 * distFactor)) {
<<<<<<< HEAD
            ofSendMessage("SetVid:3");
            ofSendMessage("NextState:1");
            ofSendMessage("moveOn");
=======
            ofSendMessage("TunnelB:0:7");
>>>>>>> develop
        }
    }
    
    //hallMesh.drawFaces();
    hallMesh.drawWireframe();
    
    ofPopMatrix();
    
    hallLight.disable();
    ofDisableLighting();
    
    camera.end();
<<<<<<< HEAD
    
    /*
    ofDrawBitmapString("goal 1: " + ofToString(camera.getPosition().squareDistance(goal1)) + " | goal 2: " + ofToString(camera.getPosition().squareDistance(goal2)), 20,20);
    
    ofDrawBitmapString("Cam x: " + ofToString(camera.getPosition().x) + " | Cam y: " + ofToString(camera.getPosition().y) + " | Cam z: " + ofToString(camera.getPosition().z), 20,50);
    
    ofDrawBitmapString(ofToString(ofGetScreenWidth()) + "  |  " + ofToString(((float)(ofGetScreenWidth()/2560.0))), 20,80);
    */
}
=======
}
//cout << hallLight.getPosition() << "  |  " << camera.getPosition() << endl;
//cout << hallLight.getIsPointLight() << "  |  " << hallLight.getIsSpotlight() << endl;
//hallLight.setOrientation(camera.getOrientationEuler());
//cout << hallLight.getSpotConcentration() << "  |  " << hallLight.getSpotlightCutOff() << endl;
//hallLight.setSpotlightCutOff(20); //andle between axis and edge of cone
//hallLight.setSpotConcentration(90); //Falloff 0-128;
//cout << hallLight.getAttenuationConstant() << "  |  " << hallLight.getAttenuationLinear() << "  |  " << hallLight.getAttenuationQuadratic() << "  |  "<< endl;
>>>>>>> develop
