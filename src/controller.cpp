/*
 *
 *
 *
 *  Main Framework for Axion. This will handle all state changes and (eventually) store history.
 *
 *
 */

#include "controller.h"
#include "states.h"



//--------------------------------------------------------------
void controller::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    helpOn = false;
    debugMessages = false;
    
    current_state = A;
    next_state = B;
    
    current_video = m0;
    
    //ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    ofEnableSeparateSpecularLight();
    

    #ifdef __APPLE__
        CGDisplayHideCursor(NULL); // <- Sometimes necessary to hide cursor on Macs
    #endif
    ofHideCursor();

    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight()/2 - ofGetHeight()/2);
    
    ofRegisterGetMessages(this);
}

//--------------------------------------------------------------
void controller::update(){
    
    sound.update();
    
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
            
        case D:
            outroPlayer.update();
            break;
            
        default:
            break;
    }
    
    fader.update();                                     // fader is what controls transition between states
    if (fader.fullCover()) {
        if (current_state == B) {
            tunnel.camera.reset();
            tunnel.camera.target(ofVec3f(0,0,1));
            //tunnel.secondTime = true;
        }
        current_state = next_state;
    }
}

//--------------------------------------------------------------
void controller::draw(){
    ofSetColor(255);
    ofBackground(0);
    
    sound.play();
    
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
                
                if (player.whichMov == 1 || player.whichMov == 2) {     // This seems a little inelegant with if/then.
                    tunnel.secondTime = true;                           //     I think there is a better way by doing this
                }                                                       //         from within the movieplayer class somehow.
                if (player.whichMov == 3) {
                    next_state = D;
                    tunnel.secondTime = false;
                    player.setFile(0);
                    fader.fadeUp();
                } else {
                    next_state = C;
                }
                
                fader.fadeUp();
            }
            break;
            
        case C:
            tunnel.draw(fader.getAlpha());
            break;
            
        case D:
            outroPlayer.draw();
            break;
            
        default:
            break;
    }
    
    drawDebugMessages();
    drawHelp();
    fader.draw();
}
//--------------------------------------------------------------
void controller::gotMessage(ofMessage& msg){
    
    // I'm using these messages to control transitions between states
    //
    // I think there is probably a better way to do it with a "State Holder" class
    // or something like that, but I didn't have too much time to play around with it.
    //
    // Let me know if you think of a better/faster idea.
    //
    //
    
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
        //cout << msg.message << endl;
        fader.moveOn();
    }
    
    if (ofIsStringInString("fadeUp", msg.message)) {
        //wcout << msg.message << endl;
        fader.fadeUp();
    }
    
}

//--------------------------------------------------------------
void controller::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void controller::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        /**************************************/
        // Debug Stuff
        case 'i':
            helpOn = !helpOn;
            break;
        
        case '0':
            if (current_state == B) {
                player.stop();
                player.reset();
                if (player.whichMov == 1 || player.whichMov == 2) {
                    tunnel.secondTime = true;
                }
                if (player.whichMov == 3) {
                    next_state = D;
                    tunnel.secondTime = false;
                    player.setFile(0);
                    fader.fadeUp();
                } else {
                    next_state = C;
                }
                
                fader.fadeUp();
            }
            break;
            
        case '1':
            if (current_state == C) {
                player.setFile(1);
                next_state = B;
                fader.moveOn();
            }
            
            break;
            
        case '2':
            if (current_state == C) {
                player.setFile(2);
                next_state = B;
                fader.moveOn();
            }
            break;
            
        case '3':
            if (current_state == C) {
                player.setFile(3);
                next_state = B;
                fader.moveOn();
            }
            break;
            
        case '.':
            debugMessages = !debugMessages;
            break;
        /**************************************/
            
        case OF_KEY_ESC:
            //
            break;
            
        default:
            if (current_state == A) {
                fader.moveOn();
            }
            break;
    }
}

//--------------------------------------------------------------
void controller::mousePressed(int x, int y, int button){
    if (current_state == A) {
        fader.moveOn();
    }
}

//--------------------------------------------------------------
void controller::drawHelp(){
    ofSetColor(255);
    switch (current_state) {
        case A:
            ofDrawBitmapString("Axion \n\nDevelopment Version: " + ofToString(VERSION, 1) + "\n\n"
                               "This is basically an app version of what we presented at CERN\n"
                               "plus some cleanup. Please let me know how it runs on your computer,\n"
                               "and let\'s use it as something to build from for Tribeca.\n\n"
                               "I\'m doing my best to squash bugs, but once it gets running on computers\n"
                               "out of my control there are sure to be things I couldn't plan for.\n\n"
                               "If something seems wrong or isn't working, press the \" i \" key for HELP.\n"
                               "Navigate the tunnel using \"W\" to move FORWARD, \"S\" to move BACK, \nand LOOK around with the MOUSE\n\n"
                               "The \" F \" key toggles Full Screen\n"
                               "The ESC key Quits\n\n"
                               "Pres ANY KEY to start!",
                               20, 20);
            break;
            
        case B:
            if (helpOn) {
                ofDrawBitmapStringHighlight("There should be a MOVIE playing here. If there isn\'t, I\'m Sorry! Please let me know.\n\n"
                                            "If it does not automatically move on, press \" 0 \" (zero)"
                                            , 20,20);
            } else {
                ofDrawBitmapStringHighlight("Press the \" i \" key for HELP", 20,20);
            }
            break;
            
        case C:
            if (helpOn) {
                ofDrawBitmapStringHighlight("Navigate the tunnel using \"W\" to move FORWARD, \"S\" to moveBACK,\n"
                                            "and LOOK around with the MOUSE\n\n"
                                            
                                            "There is nothing keeping you from walking through the walls. This will be addressed.\n\n"
                                            "If you get to the end of the hall to the left and nothing is happening, press \"1\" \n"
                                            "If you get to the end of the hall to the right and nothing is happening, press \"2\" \n"
                                            "If this is your second time through the hallway and you cannot move on, press \"3\" \n\n"
                                            "",
                                            20,20);
            } else {
                ofDrawBitmapStringHighlight("Press the \" i \" key for HELP", 20,20);
            }
            break;
            
        case D:
            ofDrawBitmapString("That\'s it for now! \n\nOn the agenda:\n"
                               "    -Add more video content\n"
                               "    -Incorporate and expand Jasmine\'s sound design\n"
                               "    -Develop another two to three hallways so we don\'t reuse the same one\n"
                               "    -Disable ability to walk through walls in the hallway\n"
                               "    -Develop one to two additional environments/experiences between videos so it\'s not just navigating a hallway\n"
                               "    -Add support for MindWave so videos are determined not just by choosing paths, but also via EEG\n"
                               "    -Jason wants to work with Jasmine to add narrative to the parts between videos (hallway, etc)\n"
                               "    -Clean up and optimize code. Find bugs and DESTROY THEM!\n\n\n"
                               "Press ESC key to QUIT"
                               , 20,20);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void controller::drawDebugMessages(){
    ofSetColor(255,0,0);
    switch (current_state) {
        case A:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()),
                                   20,ofGetHeight() - 50);
            }
            break;
            
        case B:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nWhich Movie: " + ofToString(player.whichMov) + " | Is playing? " + ofToString(player.isPlaying()) +
                                   " | Which File: " + player.getPath(),
                                   20,ofGetHeight() - 50);
                //+ player.getPath()
            }
            break;
            
        case C:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nCamera Position: (" + ofToString(tunnel.camera.getPosition().x,2) + "," +
                                   ofToString(tunnel.camera.getPosition().y,2) + "," + ofToString(tunnel.camera.getPosition().z,2) + ") | " +
                                   "Goal 1: (" + ofToString(tunnel.goal1.x,2) + "," + ofToString(tunnel.goal1.y,2) + "," + ofToString(tunnel.goal1.z,2) + ") | " +
                                   "Goal 1 Distance: " + ofToString(tunnel.camera.getPosition().squareDistance(tunnel.goal1),2) +
                                   "\nGoal 2: (" + ofToString(tunnel.goal2.x,2) + "," + ofToString(tunnel.goal2.y,2) + "," + ofToString(tunnel.goal2.z,2) + ") | " +
                                   " | Goal 2 Distance: " + ofToString(tunnel.camera.getPosition().squareDistance(tunnel.goal2),2) + " | Distance Factor: " +
                                   ofToString(tunnel.distFactor,2) + " | Second Time? " + ofToString(tunnel.secondTime),
                                   20,ofGetHeight() - 50);
            }
            break;
            
        case D:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                            " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                            " | Window Size: " + ofToString(ofGetWidth(),2) + "," + ofToString(ofGetHeight()),
                                            20,ofGetHeight() - 50);
            }
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void controller::exit(){
    
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
void controller::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void controller::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void controller::dragEvent(ofDragInfo dragInfo){
    
}
