/*
 *
 *
 *
 *  Main Framework for Axion. This will handle all state changes and store history.
 *
 *
 */

#include "controller.h"



//--------------------------------------------------------------
void controller::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    /*
    camera.setup();
    camTargSet = false;
    camera.speed =  0.8f;
    camera.sensitivityX = 0.05f;
    camera.sensitivityY = 0.05f;
    camera.accel = 0.05f;
    camera.disableMove();
    camera.disableStrafe();
    */
    
    current_state = C;
    next_state = B;
    
    current_video = m0;
    
    //ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    ofEnableSeparateSpecularLight();
    

    #ifdef __APPLE__
        CGDisplayHideCursor(NULL); // <- Sometimes necessary to hide curson on Macs
    #endif
    ofHideCursor();

    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight()/2 - ofGetHeight()/2);
    
    ofRegisterGetMessages(this);
}

//--------------------------------------------------------------
void controller::update(){
    switch (current_state) {
        case A:
            introPlayer.update();
            break;
        
        case B:
            player.update();
            break;
            
        case C:
            tunnel.update();
            break;
            
        default:
            break;
    }
    
    fader.update();
    if (fader.fullCover()) {
        if (current_state == B) {
            tunnel.camera.reset();
            tunnel.camera.target(ofVec3f(0,0,1));
        }
        current_state = next_state;
    }
}

//--------------------------------------------------------------
void controller::draw(){
    ofSetColor(255);
    ofBackground(0);
    
    switch (current_state) {
        case A:
            introPlayer.draw();
            next_state = B;
            break;
        case B:
            player.play();
            player.draw(0, 0, ofGetWidth(), ofGetHeight());
            
            if (player.isDone) {
                player.stop();
                player.reset();
                next_state = C;
                fader.fadeUp();
            }
            break;
            
        case C:
            tunnel.draw(fader.getAlpha());
            break;
            
        default:
            break;
    }
    fader.draw();
}
//--------------------------------------------------------------
void controller::gotMessage(ofMessage& msg){
    
    if (ofIsStringInString(msg.message, "SetVid")) {
        int vid = ofToInt(ofSplitString(msg.message, ":")[1]);
        //cout << "vid will be: " << state << endl;
        player.setFile(vid);
        
    }
    
    if (ofIsStringInString(msg.message, "NextState")) {
        int state = ofToInt(ofSplitString(msg.message, ":")[1]);
        //cout << "state will be: " << state << endl;
        if (state == 0) {
            next_state = A;
        } else if (state == 1) {
            next_state = B;
        } else if (state == 2) {
            next_state = C;
        } else if (state == 3) {
            next_state = D;
        }
    }
    
    if (ofIsStringInString("moveOn", msg.message)) {
        cout << msg.message << endl;
        fader.moveOn();
    }
    
    if (ofIsStringInString("fadeUp", msg.message)) {
        cout << msg.message << endl;
        fader.fadeUp();
    }
    
}

//--------------------------------------------------------------
void controller::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        
        case OF_KEY_ESC:
            //
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void controller::keyReleased(int key){

}

//--------------------------------------------------------------
void controller::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void controller::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void controller::mousePressed(int x, int y, int button){
    //current_state = B;
    
    if (current_state == A) {
        fader.moveOn();
    }

}

//--------------------------------------------------------------
void controller::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void controller::windowResized(int w, int h){

}

//--------------------------------------------------------------
void controller::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void controller::dragEvent(ofDragInfo dragInfo){ 

}
