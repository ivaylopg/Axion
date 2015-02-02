#include "iss.h"

//--------------------------------------------------------------
Iss::Iss(){
    setup();
}

//--------------------------------------------------------------
void Iss::setup() {
    isPaused = false;
    counter = 0;
    
    spaceSounds.loadSound("audio/2b.aiff");
    
    spaceSounds.setMultiPlay(false);
    spaceSounds.setLoop(false);
//    spaceSounds.setPan(-1.0f);
    spaceSounds.setVolume(1.0);
//    spaceSounds.play();
    playedOnce = false;
    
    
    showFR = true;
    
    cam.setup();
    cam.reset(-100);
    cam.loadCameraPosition();
    //cam.lockHeight = false;
    cam.setMinMaxY(40, 40);
    cam.speed = 4.0f;
    //cam.upDir = ofVec3f(0,-1,0);
    cam.flipCam();
    
    station.loadModel("ISS/ISS3_3DS/iss.3ds");
    station.setPosition(0, 0, 0);
    station.update();
    //stationMesh = station.getCurrentAnimatedMesh(0);
    
    ams.loadModel("ISS/ams.obj");
    ams.setScale(0.05, 0.05, 0.05);
    //ams.setRotation(0, 90, 1.0, 0.0, 0.0);
    //ams.setPosition(-165, -25, 5);
    ams.setPosition(-185, -10, 5);
    ams.update();
    
    starSphere.setRadius(10000);
    starSphere.setResolution(48);
    starSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    
    earthSphere.setRadius(8000);
    earthSphere.setResolution(48);
    earthSphere.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofDisableArbTex();
    stars.loadImage("ISS/TychoStars.jpg");
    stars.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    earth.loadImage("ISS/Earth/earth_cloudy_diffuse_bw.jpg");
    earth.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    
    distFactor = ((float)ofGetScreenWidth())/2560.0;
    
    light.setPosition(-800 * distFactor, -540 * distFactor, 500 * distFactor);
    light2.setPosition(-1920 * distFactor, -1080 * distFactor, -500 * distFactor);
    //light.setPosition(0, 0, 0);
    //light2.setPosition(0, 0, 0);
    
    cam.setFarClip(20000.0);
    eSpin = -0.01;
    labelPos = ofVec3f(0,0,0);
    labelHeight = 50;

}

//--------------------------------------------------------------
void Iss::update() {
    cout << spaceSounds.getPosition() << endl;
    if (spaceSounds.getPosition() >= 0.99) {
        ofSendMessage("TunnelB:0:7");
    }
    
    if (!spaceSounds.getIsPlaying() && !playedOnce) {
        spaceSounds.play();
    } else if (spaceSounds.getIsPlaying()){
        playedOnce = true;
    }
    
    earthSphere.rotate(eSpin, 0, 1.0, 0.0);
}

//--------------------------------------------------------------
void Iss::draw() {
    cam.begin();
    ofSetColor(255, 0, 0);
    //ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(255);
    
    starsM.begin();
    //ofSetColor(255, 0, 0);
    ofSetColor(255);
    stars.getTextureReference().bind();
    starSphere.setPosition(0,0,0);
    starSphere.draw();
    ofSetColor(255);
    stars.getTextureReference().unbind();
    starsM.end();

    earthM.begin();
    //ofSetColor(0, 0, 255);
    ofSetColor(64);
    earth.getTextureReference().bind();
    earthSphere.setPosition(8000,4000,4000);
    earthSphere.draw();
    ofSetColor(255);
    earth.getTextureReference().unbind();
    earthM.end();
    
    ofEnableLighting();
    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable();
    light2.enable();
    ofEnableSeparateSpecularLight();
    
    ofSetColor(200);
    //station.drawWireframe();
    station.drawFaces();
    ofSetColor(255);
    
    ofSetColor(180,0,0,255);
    
    ofPushMatrix();
    ofTranslate(ams.getPosition().x, ams.getPosition().y,ams.getPosition().z);
    //ofTranslate(ams.getPosition());
    ofRotateY(-90);
    ofRotateX(-90);
    //ofTranslate(ams.getPosition().scale(-1.0));
    ofTranslate(-ams.getPosition().x, -ams.getPosition().y,-ams.getPosition().z);
    ams.drawFaces();
    ofPopMatrix();
    
    ofSetColor(255,255,255,255);
    
    light.disable();
    light2.disable();
    ofDisableLighting();
    
    //double dist = ofDistSquared(ams.getPosition().x, ams.getPosition().z, cam.getPosition().x, cam.getPosition().z);
    //cam.speed = ofMap(dist, 5000, 500000, 4.0 * (60/ofGetFrameRate()), 7.0 * (60/ofGetFrameRate()),true);
    
    cam.end();

}

//--------------------------------------------------------------
void Iss::pause(bool b) {
    isPaused = b;
}

//--------------------------------------------------------------
void Iss::resetCamera() {
    playedOnce = false;
    spaceSounds.setPosition(0.0);
    
    
}