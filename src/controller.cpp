#include "controller.h"



//--------------------------------------------------------------
void controller::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    current_state = A;
    next_state = B;
    
    current_video = m0;
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    ofEnableSeparateSpecularLight();
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
}

//--------------------------------------------------------------
void controller::draw(){
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
            tunnel.draw();
            break;
            
        default:
            break;
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
