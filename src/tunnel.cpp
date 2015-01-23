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
    
    camera.setup();
    camTargSet = false;
    camera.speed =  1.0f;
    //camera.speed =  1.0f;
    camera.sensitivityX = 0.05f;
    camera.sensitivityY = 0.05f;
    camera.accel = 0.02f;
    camera.disableMove();
    camera.disableStrafe();
    
    camPos = ofVec3f(0,0,0);
    
    distFactor = ((float)ofGetScreenWidth())/2560.0;
    
    goal1 = ofVec3f(442,0,854) * distFactor;
    goal2 = ofVec3f(-317,0,1175) * distFactor;
    
    hallModel.update();
    hallMesh = hallModel.getCurrentAnimatedMesh(0);
    
    secondTime = false;
    isPaused = false;
    hallWidth = 10.0 * distFactor;
    isClipping = true;
}

//--------------------------------------------------------------
void Tunnel::update(){
    //hallModel.update();
    //hallMesh = hallModel.getCurrentAnimatedMesh(0);
    
    /*
    float accel = 0.05 * (60/ofGetFrameRate());
    camera.accel = ofClamp(accel, 0.05, 0.2);
    //*/
    
    //*
    float camSpeed = 1.0f * (60/ofGetFrameRate());
    camera.speed = ofClamp(camSpeed,1.0,2.0);
    //*/
    
    /*
    float sensitivity = 0.05f * (60/ofGetFrameRate());
    sensitivity = ofClamp(sensitivity, 0.05, 0.2);
    camera.sensitivityX = sensitivity;
    camera.sensitivityY = sensitivity;
    //*/
}

//--------------------------------------------------------------
void Tunnel::pause(bool b){
    isPaused = b;
    if (b) {
        camera.disableMove();
    } else {
        camera.enableMove();
    }
}

//--------------------------------------------------------------
void Tunnel::draw(float alph){
    if (!isPaused) {
        camera.enableMove();
    }
    camera.begin();
    if (!camTargSet) {
        camera.target(ofVec3f(0,0,1));
        camTargSet = true;
    }
    
    camPos = camera.getPosition();
	hallLight.enable();

    if (!secondTime) {
        hallLight.setPosition(camera.getPosition());
        float attenuationFactor = 0.008 * (2560.0/ofGetScreenWidth());
        hallLight.setAttenuation(0,attenuationFactor,0);
    } else {
        hallLight.setPosition(0,0,0);
        hallLight.setAttenuation(1,0,0);
    }
    
    ofPushMatrix();
    ofSetColor(255,255-alph);
    glLineWidth(1);
    
    ofxAssimpMeshHelper & meshHelper = hallModel.getMeshHelper(0);
    ofMultMatrix(hallModel.getModelMatrix());
    ofMultMatrix(meshHelper.matrix);


    //*
    
    if (isClipping) {
    
        ofVec3f testPos = camPos;                       //Hacky-ass clipping
        
        
        if (testPos.x < goal2.x + hallWidth) {
            if (testPos.x < goal2.x-hallWidth) {
                testPos.x = goal2.x-hallWidth;
            }
        }
        
        if ((testPos.z >= goal1.z && testPos.x > goal2.x+hallWidth*1.5) || (testPos.z <= goal1.z-hallWidth && abs(testPos.x) >= hallWidth*1.5)) {
            if (testPos.z > goal1.z+(hallWidth*0.8)) {
                testPos.z = goal1.z+(hallWidth*0.8);
            } else if (testPos.z < goal1.z-(hallWidth)) {
                testPos.z = goal1.z-(hallWidth);
            }
        }
        
        if (testPos.x > goal2.x+hallWidth && testPos.z >= goal1.z+hallWidth*1.5){
            testPos.x = goal2.x+hallWidth;
        }
        
        if (testPos.z < goal1.z-hallWidth && abs(testPos.x) < hallWidth*1.5) {
            if (testPos.x > hallWidth){
                testPos.x = hallWidth;
            } else if (camPos.x < -hallWidth) {
                testPos.x = -hallWidth;
            }
            
            if (testPos.z < -53 * distFactor) {
                testPos.z = -53 * distFactor;
            }
        }
        
        if (testPos != camPos) {
            camera.clip(testPos);
        }
    }
    //cout << "camPos.z: " << camPos.z << " | camPos.z: " << camPos.z/distFactor << endl;

    //*/
    
    if (!secondTime) {
        if (camera.getPosition().squareDistance(goal1) < (4900.0 * distFactor)) {
            ofSendMessage("TunnelA:1:3");
        }
        
        if (camera.getPosition().squareDistance(goal2) < (4900.0 * distFactor)) {
            ofSendMessage("TunnelA:2:3");
        }
    }
    
    if (secondTime) {
        if (camera.getPosition().squareDistance(goal1) < (250000.0 * distFactor) || camera.getPosition().squareDistance(goal2) < (250000.0 * distFactor)) {
            ofSendMessage("TunnelB:0:7");
        }
    }
    
    //hallMesh.drawFaces();
    hallMesh.drawWireframe();
    
    
    
    ofPopMatrix();
    
    hallLight.disable();
    ofDisableLighting();
    
    camera.end();
    
    
}



//cout << hallLight.getPosition() << "  |  " << camera.getPosition() << endl;
//cout << hallLight.getIsPointLight() << "  |  " << hallLight.getIsSpotlight() << endl;
//hallLight.setOrientation(camera.getOrientationEuler());
//cout << hallLight.getSpotConcentration() << "  |  " << hallLight.getSpotlightCutOff() << endl;
//hallLight.setSpotlightCutOff(20); //andle between axis and edge of cone
//hallLight.setSpotConcentration(90); //Falloff 0-128;
//cout << hallLight.getAttenuationConstant() << "  |  " << hallLight.getAttenuationLinear() << "  |  " << hallLight.getAttenuationQuadratic() << "  |  "<< endl;


//--------------------------------------------------------------
void Tunnel::toggleClipping() {
    isClipping = !isClipping;
}