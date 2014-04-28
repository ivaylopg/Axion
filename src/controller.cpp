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
    
<<<<<<< HEAD
=======
    ofResetElapsedTimeCounter();
    ofLog(OF_LOG_NOTICE) << "NEW USER - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << "\n";
    
>>>>>>> develop
    helpOn = false;
    debugMessages = false;
    
    current_state = A;
    next_state = B;
    
<<<<<<< HEAD
    current_video = m0;
=======
    mind.reset();
    
    volume = 0.65;
>>>>>>> develop
    
    //ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    ofEnableSeparateSpecularLight();
    
<<<<<<< HEAD
=======
    tunnel1.secondTime = false;
    lastMessage = " ";
>>>>>>> develop

    #ifdef __APPLE__
        CGDisplayHideCursor(NULL); // <- Sometimes necessary to hide cursor on Macs
    #endif
    ofHideCursor();

    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight()/2 - ofGetHeight()/2);
    
    ofRegisterGetMessages(this);
<<<<<<< HEAD
=======
    
    vids01.clear();
    vids02.clear();
    vids03.clear();
    vids04.clear();
    
    vids01.push_back("mov/0.mov");
    
    vids02.push_back("mov/1.mov");
    vids02.push_back("mov/2.mp4");
    vids02.push_back("mov/3.mov");
    vids02.push_back("mov/4.mov");
    
    vids04.push_back("mov/5.mp4");
    vids04.push_back("mov/6.mov");
    
    playerIntro.setup(vids01.size());
    playerBranch1.setup(vids02.size());
    //playerBranch2.setup(vids03.size());
    playerOutro.setup(vids04.size());
    
    playerIntro.load(vids01);
    
>>>>>>> develop
}

//--------------------------------------------------------------
void controller::update(){
<<<<<<< HEAD
    
    sound.update();
    
    switch (current_state) {
        case A:
=======
    mind.update();
    //sound.update();
    
    switch (current_state) {
        case A:
            if (sound.volume < volume) {
                sound.fadeUp();
            }
>>>>>>> develop
            introPlayer.update();
            break;
        
        case B:
<<<<<<< HEAD
            player.update();
            break;
            
        case C:
            tunnel.update();
            break;
            
        case D:
=======
            if (sound.volume > volume/3) {
                sound.fadeDown();
            }
            playerIntro.update();
            break;
            
        case C:
            if (sound.volume < volume) {
                sound.fadeUp();
            }
            tunnel1.update();
            break;
            
        case D:
            if (sound.volume > 0) {
                sound.fadeDown();
            }
            if (sound.volume <= 0) {
                sound.newFile("audio/3.aiff");
            }
            playerBranch1.update();
            break;
            
        case E:
            //outroPlayer.update();
            break;
            
        case F:
            if (sound.volume > volume/3) {
                sound.fadeDown();
            }
            playerBranch2.update();
            break;
            
        case G:
            /////////////////////
            break;
            
        case H:
            if (sound.volume > 0) {
                sound.fadeDown();
            }
            playerOutro.update();
            break;
            
        case I:
            if (sound.volume < volume) {
                sound.fadeUp();
            }
>>>>>>> develop
            outroPlayer.update();
            break;
            
        default:
            break;
    }
    
<<<<<<< HEAD
    fader.update();                                     // fader is what controls transition between states
    if (fader.fullCover()) {
        if (current_state == B) {
            tunnel.camera.reset();
            tunnel.camera.target(ofVec3f(0,0,1));
=======
    sound.update();
    
    fader.update();                                     // fader is what controls transition between states
    if (fader.fullCover()) {
        if (current_state != C && next_state == C) {
            tunnel1.camera.reset();
            tunnel1.camera.target(ofVec3f(0,0,1));
>>>>>>> develop
            //tunnel.secondTime = true;
        }
        current_state = next_state;
    }
<<<<<<< HEAD
=======
    
    //cout << "Diff 10: " << mind.diff10() << " | Diff 20:" << mind.diff20() << endl;
>>>>>>> develop
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
<<<<<<< HEAD
            player.play();
            player.draw(0, 0, ofGetWidth(), ofGetHeight());
            
            if (player.isDone) {
                player.stop();
                player.reset();
                
=======
            playerIntro.play();
            playerIntro.draw(0, 0, ofGetWidth(), ofGetHeight());
            
            if (playerIntro.isDone) {
                //playerIntro.stop();
                //playerIntro.reset();
                /*
>>>>>>> develop
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
<<<<<<< HEAD
                
=======
                */
                next_state = C;
                playerIntro.clear();
>>>>>>> develop
                fader.fadeUp();
            }
            break;
            
        case C:
<<<<<<< HEAD
            tunnel.draw(fader.getAlpha());
            break;
            
        case D:
            outroPlayer.draw();
=======
            tunnel1.draw(fader.getAlpha());
            if (!tunnel1.secondTime) {
                playerBranch1.load(vids02);
            } else if (tunnel1.secondTime) {
                playerOutro.load(vids04);
            }
            break;
            
        case D:
            playerBranch1.play();
            playerBranch1.draw(0, 0, ofGetWidth(), ofGetHeight());
            
            if (playerBranch1.isDone) {
                next_state = C;
                tunnel1.secondTime = true;
                playerBranch1.clear();
                fader.fadeUp();
            }
            break;
            
        case E:
            //outroPlayer.draw();
            break;
            
        case F:
            playerBranch2.play();
            playerBranch2.draw(0, 0, ofGetWidth(), ofGetHeight());
            
            if (playerBranch2.isDone) {
                next_state = C;
                tunnel1.secondTime = true;
                playerBranch2.clear();
                fader.fadeUp();
            }
            break;
            
        case G:
            //outroPlayer.draw();
            break;
            
        case H:
            playerOutro.play();
            playerOutro.draw(0, 0, ofGetWidth(), ofGetHeight());
            
            if (playerOutro.isDone) {
                next_state = I;
                playerOutro.clear();
                fader.fadeUp();
            }
            break;
            
        case I:
                outroPlayer.draw();
>>>>>>> develop
            break;
            
        default:
            break;
    }
    
    drawDebugMessages();
<<<<<<< HEAD
    drawHelp();
=======
    //drawHelp();
>>>>>>> develop
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
    
<<<<<<< HEAD
    if (ofIsStringInString(msg.message, "SetVid")) {
        int vid = ofToInt(ofSplitString(msg.message, ":")[1]);
        //cout << "vid will be: " << state << endl;
        player.setFile(vid);
        
=======
    if (msg.message == lastMessage) {
        return;
    } else {
        lastMessage = msg.message;
    }
    
    if (ofIsStringInString(msg.message, "TunnelA")) {
        int branch = ofToInt(ofSplitString(msg.message, ":")[1]);
        int state = ofToInt(ofSplitString(msg.message, ":")[2]);
        cout << "Sent to Brancher from Tunnel A" << endl;
        ofLog(OF_LOG_NOTICE) << "Sent to Brancher from Tunnel A - " << ofGetElapsedTimeMillis() << "\n";
        brancher(1, branch, state);
    }
    
    if (ofIsStringInString(msg.message, "TunnelB")) {
        int branch = ofToInt(ofSplitString(msg.message, ":")[1]);
        int state = ofToInt(ofSplitString(msg.message, ":")[2]);
        cout << "Sent to Brancher from Tunnel B" << endl;
        ofLog(OF_LOG_NOTICE) << "Sent to Brancher from Tunnel B - " << ofGetElapsedTimeMillis() << "\n";
        brancher(2, branch, state);
    }
    
    
    
    if (ofIsStringInString(msg.message, "SetVid")) {
        int vid = ofToInt(ofSplitString(msg.message, ":")[1]);
        //cout << "vid will be: " << state << endl;
        if (!tunnel1.secondTime) {
            playerBranch1.setFile(vid);
        } else {
            playerOutro.setFile(vid);
        }
>>>>>>> develop
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
<<<<<<< HEAD
=======
        } else if (state == 4) {
            next_state = E;
        } else if (state == 5) {
            next_state = F;
        } else if (state == 6) {
            next_state = G;
        } else if (state == 7) {
            next_state = H;
        } else if (state == 8) {
            next_state = I;
>>>>>>> develop
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
<<<<<<< HEAD
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
=======
            //helpOn = !helpOn;
            break;
        
        case '0':
            current_state = next_state;
>>>>>>> develop
            break;
            
        case '.':
            debugMessages = !debugMessages;
            break;
        /**************************************/
            
        case OF_KEY_ESC:
            //
            break;
            
<<<<<<< HEAD
=======
        case ';':
            if (current_state == I) {
                ofLog(OF_LOG_NOTICE) << "RESTARTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << "\n";
                sound.volume == 0;
                sound.newFile("audio/1.aiff");
                setup();
            }
            break;
            
>>>>>>> develop
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
<<<<<<< HEAD
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
            
=======
>>>>>>> develop
        case B:
            if (helpOn) {
                ofDrawBitmapStringHighlight("There should be a MOVIE playing here. If there isn\'t, I\'m Sorry! Please let me know.\n\n"
                                            "If it does not automatically move on, or if it keeps looping, press \" 0 \" (zero)"
                                            , 20,20);
<<<<<<< HEAD
            } else {
                ofDrawBitmapStringHighlight("Press the \" i \" key for HELP", 20,20);
=======
>>>>>>> develop
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
<<<<<<< HEAD
            } else {
                ofDrawBitmapStringHighlight("Press the \" i \" key for HELP", 20,20);
=======
>>>>>>> develop
            }
            break;
            
        case D:
<<<<<<< HEAD
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
=======
            if (helpOn) {
                ofDrawBitmapStringHighlight("There should be a MOVIE playing here. If there isn\'t, I\'m Sorry! Please let me know.\n\n"
                                            "If it does not automatically move on, or if it keeps looping, press \" 0 \" (zero)"
                                            , 20,20);
            }
>>>>>>> develop
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
<<<<<<< HEAD
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()),
                                   20,ofGetHeight() - 50);
=======
        case I:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()),
                                   20,ofGetHeight() - 70);
>>>>>>> develop
            }
            break;
            
        case B:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
<<<<<<< HEAD
                                   "\nWhich Movie: " + ofToString(player.whichMov) + " | Is playing? " + ofToString(player.isPlaying()) +
                                   " | Which File: " + player.getPath(),
                                   20,ofGetHeight() - 50);
                //+ player.getPath()
            }
            break;
            
        case C:
=======
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nWhich Movie: " + ofToString(playerIntro.whichMov) + " | Is playing? " + ofToString(playerIntro.isPlaying()) +
                                   " | Which File: " + playerIntro.getPath(),
                                   20,ofGetHeight() - 70);
            }
            break;
            
        case D:
>>>>>>> develop
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
<<<<<<< HEAD
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
            
=======
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nWhich Movie: " + ofToString(playerBranch1.whichMov) + " | Is playing? " + ofToString(playerBranch1.isPlaying()) +
                                   " | Which File: " + playerBranch1.getPath(),
                                   20,ofGetHeight() - 70);
            }
            break;
            
        case F:
            break;
            
        case H:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nWhich Movie: " + ofToString(playerOutro.whichMov) + " | Is playing? " + ofToString(playerOutro.isPlaying()) +
                                   " | Which File: " + playerOutro.getPath(),
                                   20,ofGetHeight() - 70);
            }
            break;
            
        case C:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nCamera Position: (" + ofToString(tunnel1.camera.getPosition().x,2) + "," +
                                   ofToString(tunnel1.camera.getPosition().y,2) + "," + ofToString(tunnel1.camera.getPosition().z,2) + ") | " +
                                   "Goal 1: (" + ofToString(tunnel1.goal1.x,2) + "," + ofToString(tunnel1.goal1.y,2) + "," + ofToString(tunnel1.goal1.z,2) + ") | " +
                                   "Goal 1 Distance: " + ofToString(tunnel1.camera.getPosition().squareDistance(tunnel1.goal1),2) +
                                   "\nGoal 2: (" + ofToString(tunnel1.goal2.x,2) + "," + ofToString(tunnel1.goal2.y,2) + "," + ofToString(tunnel1.goal2.z,2) + ") | " +
                                   " | Goal 2 Distance: " + ofToString(tunnel1.camera.getPosition().squareDistance(tunnel1.goal2),2) + " | Distance Factor: " +
                                   ofToString(tunnel1.distFactor,2) + " | Second Time? " + ofToString(tunnel1.secondTime),
                                   20,ofGetHeight() - 70);
            }
            break;
            
            
>>>>>>> develop
        default:
            break;
    }
}

//--------------------------------------------------------------
<<<<<<< HEAD
void controller::exit(){
    
=======
void controller::brancher(int source, int branch, int state){
    
    if (state == 0) {
        next_state = A;
    } else if (state == 1) {
        next_state = B;
    } else if (state == 2) {
        next_state = C;
    } else if (state == 3) {
        next_state = D;
    } else if (state == 4) {
        next_state = E;
    } else if (state == 5) {
        next_state = F;
    } else if (state == 6) {
        next_state = G;
    } else if (state == 7) {
        next_state = H;
    } else if (state == 8) {
        next_state = I;
    }
    

    if (source==1) {
        if (mind.hasNewInfo()) {
            if (mind.diff20() > -100.0) {
                if (mind.diff20()>10) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Attentive - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(0);
                } else if (mind.diff20()>0){
                    // SOMEWHAT Attentive
                    cout << "SOMEWHAT Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Attentive - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(1);
                } else if (mind.diff20()<-10) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Meditative - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(3);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Meditative - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(2);
                }
            } else if (mind.diff10() > -100.0) {
                if (mind.diff10()>10) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Attentive - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(0);
                } else if (mind.diff10()>0){
                    // SOMEWHAT Attentive
                    cout << "SOMEWHAT Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Attentive - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(1);
                } else if (mind.diff10()<-10) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Meditative - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(3);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Meditative - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerBranch1.setFile(2);
                }
            } else {
                // Cannot Determine
                cout << "Cannot Determine" << endl;
                ofLog(OF_LOG_NOTICE) << "Cannot Determine - Branch 1 - " << ofGetElapsedTimeMillis() << "\n";
                playerBranch1.setFile(branch);
            }
        } else {
            // NO EEG DATA
            cout << "NO EEG DATA" << endl;
            ofLog(OF_LOG_NOTICE) << "No EEG Data - Branch 1 - " << ofGetElapsedTimeMillis() << "\n";
            playerBranch1.setFile(branch);
        }
        
    } else if (source == 2){
        if (mind.hasNewInfo()) {
            if (mind.diff20() > -100.0) {
                if (mind.diff20()>10) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Attentive - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(0);
                } else if (mind.diff20()>0){
                    // SOMEWHAT Attentive
                    cout << "SOMEWHAT Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Attentive - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(0);
                } else if (mind.diff20()<-10) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Meditative - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(1);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Meditative - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(1);
                }
            } else if (mind.diff10() > -100.0) {
                if (mind.diff10()>10) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Attentive - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(0);
                } else if (mind.diff10()>0){
                    // SOMEWHAT Attentive
                    cout << "Somewhat Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Attentive - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(0);
                } else if (mind.diff10()<-10) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Very Meditative - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(1);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "Somewhat Meditative - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << "\n";
                    playerOutro.setFile(1);
                }
            } else {
                // Cannot Determine
                cout << "Cannot Determine" << endl;
                ofLog(OF_LOG_NOTICE) << "Cannot Determine - Branch 2 - " << ofGetElapsedTimeMillis() << "\n";
                playerOutro.setFile(floor(ofRandom(2)));
            }
        } else {
            // NO EEG DATA
            cout << "NO EEG DATA" << endl;
            ofLog(OF_LOG_NOTICE) << "No EEG Data - Branch 2 - " << ofGetElapsedTimeMillis() << "\n";
            playerOutro.setFile(floor(ofRandom(2)));
        }
    }
    
    fader.moveOn();
    
}

//--------------------------------------------------------------
void controller::exit(){
    mind.free();
    ofLog(OF_LOG_NOTICE) << "QUITTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << "\n";
>>>>>>> develop
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
