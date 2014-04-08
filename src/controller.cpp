#include "controller.h"



//--------------------------------------------------------------
void controller::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    camera.setup();
    camTargSet = false;
    camera.speed =  0.8f;
    camera.sensitivityX = 0.05f;
    camera.sensitivityY = 0.05f;
    camera.accel = 0.05f;
    camera.disableMove();
    camera.disableStrafe();
    
    current_state = A;
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
}

//--------------------------------------------------------------
void controller::draw(){
    ofSetColor(255);
    ofBackground(0);
    
    switch (current_state) {
        case A:
            introPlayer.draw();
            break;
        case B:
            player.play();
            player.draw(0, 0, ofGetWidth(), ofGetHeight());
            if (player.isDone) {
                player.stop();
                player.reset();
                current_state = C;
            }
            break;
            
        case C:
            camera.enableMove();
            camera.begin();
            if (!camTargSet) {
                camera.target(ofVec3f(0,0,1));
                camTargSet = true;
            }
            tunnel.draw();
            camera.end();
            break;
            
        default:
            break;
    }
    
    
    fader.draw();
    
    
    
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
    current_state = B;

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
