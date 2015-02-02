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
    ofSetEscapeQuitsApp(false);
    
#ifdef OF_RELEASE
    cout << "You are in Release Mode!" << endl;
#elif OF_DEBUG
    cout << "You are in Debug Mode!" << endl;
#endif
    
    ofResetElapsedTimeCounter();
    ofLog(OF_LOG_NOTICE) << "##################" << "\n" << "------------- NEW USER - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << "\n";
    
    helpOn = false;
    debugMessages = false;
    isPaused = false;
    
    current_state = C;
    next_state = B;
    
    mind.reset();
    usingEEG = true;
    
    volume = 0.65;
    
    //ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    ofEnableSeparateSpecularLight();
    
    tunnel1.secondTime = false;
    explorePrompt.loadImage("explore.png");
    imgAlpha = 255;
    exploreCounter = 0;
    timeFade = false;
    
    lastMessage = " ";

    #ifdef __APPLE__
        CGDisplayHideCursor(NULL); // <- Sometimes necessary to hide cursor on Macs
    #endif
    ofHideCursor();

    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, ofGetScreenHeight()/2 - ofGetHeight()/2);
    
    ofRegisterGetMessages(this);
    
    vids01.clear();
    vids02.clear();
    vids03.clear();
    vids04.clear();
    
    vids01.push_back("mov/0.mp4");
    
    vids02.push_back("mov/1.mp4");
    vids02.push_back("mov/2.mp4");
    vids02.push_back("mov/3.mp4");
    vids02.push_back("mov/4.mp4");
    
    vids04.push_back("mov/5.mp4");
    vids04.push_back("mov/6.mp4");
    
    playerIntro.setup(vids01.size());
    playerBranch1.setup(vids02.size());
    //playerBranch2.setup(vids03.size());
    playerOutro.setup(vids04.size());
    
    playerIntro.load(vids01);
    
    ofAddListener(introPlayer.progControl, this, &controller::controlEvent);
    ofAddListener(mind.pushedBack, this, &controller::updateEegVis);
    //ofAddListener(mind.thinkGear.meditationChangeEvent, this, &controller::controlEvent);
    
    mainGraphics.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    mainGraphics.begin();
    ofClear(255,255,255, 0);
    mainGraphics.end();
    introPlayer.firstTime = true;
    introPlayer.counter = 0;
    introPlayer.firstAlpha = 0;
    
    ida.newFile("audio/woodenBoxLoopEQ.aiff");
    ida.pause(true);
}

//--------------------------------------------------------------
void controller::update(){
    //ofSoundUpdate();
    
    if (usingEEG) {
        mind.update();
    }
    
    //sound.update();
    
    switch (current_state) {
        case A:
            if (sound.volume < volume/2) {
                sound.fadeUp();
            }
            if (usingEEG) {
                introPlayer.update(mind.getSignalQuality());
            }
            outroPlayer.resetScroll();
            break;
        
        case B:
            if (sound.volume > 0) {
                sound.fadeDown();
            }
            playerIntro.pause(isPaused);
            playerIntro.update();
            break;
            
        case C:
            if (sound.volume < volume) {
                sound.fadeUp();
            }
            tunnel1.pause(isPaused);
            tunnel1.update();
            break;
            
        case D:
            if (sound.volume > 0) {
                sound.fadeDown();
            }
            if (sound.volume <= 0) {
                //sound.newFile("audio/3.aiff"); // "unfinished journey"
                sound.newFile("audio/1.aiff");
            }
            playerBranch1.pause(isPaused);
            playerBranch1.update();
            break;
            
        case E:
            //outroPlayer.update();
            if (sound.volume < volume/3) {
                sound.fadeUp();
            } else {
                sound.volume = volume/3;
            }
            iss.pause(isPaused);
            iss.update();
            break;
            
        case F:
            if (sound.volume > volume/3) {
                sound.fadeDown();
            }
            playerBranch2.pause(isPaused);
            playerBranch2.update();
            break;
            
        case G:
            /////////////////////
            break;
            
        case H:
            if (sound.volume > 0) {
                sound.fadeDown();
            }
            playerOutro.pause(isPaused);
            playerOutro.update();
            break;
            
        case I:
            if (sound.volume < volume/3) {
                sound.fadeUp();
            } else {
                sound.volume = volume/3;
            }
            outroPlayer.update();
            break;
            
        default:
            break;
    }
    
    sound.update();
    
    fader.update();                                     // fader is what controls transition between states
    if (fader.fullCover()) {
        if (current_state != C && next_state == C) {
            tunnel1.camera.reset();
            tunnel1.camera.target(ofVec3f(0,0,1));
            //tunnel.secondTime = true;
        }
        if (current_state != E && next_state == E) {
            iss.resetCamera();
            //tunnel.secondTime = true;
        }
        current_state = next_state;
        
        if (current_state != A && current_state != I && !isPaused) {
            if (current_state == D) {
                vis.updateBranches(current_state,playerBranch1.getPath());
            } else if (current_state == F) {
                vis.updateBranches(current_state,playerBranch2.getPath());
            } else if (current_state == H) {
                vis.updateBranches(current_state,playerOutro.getPath());
            //} else if (current_state == C && tunnel1.secondTime){
            } else if (current_state == E){
                vis.updateBranches(current_state, "second");
            } else {
                vis.updateBranches(current_state);
            }
        }
    }
    
    /*
    if (current_state != A && current_state != I && !isPaused) {
        if (current_state == D) {
            vis.updateBranches(current_state,playerBranch1.getPath());
        } else if (current_state == F) {
            vis.updateBranches(current_state,playerBranch2.getPath());
        } else if (current_state == H) {
            vis.updateBranches(current_state,playerOutro.getPath());
        } else {
            vis.updateBranches(current_state);
        }
    }
    */
    //cout << "Diff 10: " << mind.diff10() << " | Diff 20:" << mind.diff20() << endl;
    
    if (current_state == A || current_state == I) {
        ida.pause(false);
        if (ida.volume < volume) {
            ida.fadeUp();
        }
    } else {
        if (ida.volume > 0) {
            ida.fadeDown();
        } else {
            ida.pause(true);
        }
    }
    ida.update();
    
    if (current_state != C) {
        tunnel1.stopSound();
    }
    ofSoundUpdate();
}

//--------------------------------------------------------------
void controller::draw(){
    ofSetColor(255);
    ofBackground(0);
    
    sound.play();
    ida.play();
    
    if (!isPaused && (current_state == A || current_state == I)) {
        switch (current_state) {
            case A:
                introPlayer.draw();
                next_state = B;
                break;
                
            case I:
                outroPlayer.draw();
                break;
                
            default:
                break;
        }
    } else if (!isPaused) {
        mainGraphics.begin();
        ofSetColor(255);
        ofBackground(0);
        
        switch (current_state) {
            case B:
                playerIntro.play();
                playerIntro.draw(0, 0, ofGetWidth(), ofGetHeight());
                
                if (playerIntro.isDone) {
                    //playerIntro.stop();
                    //playerIntro.reset();
                    /*
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
                     */
                    next_state = C;
                    playerIntro.clear();
                    fader.fadeUp();
                }
                break;
                
            case C:
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
                    next_state = E;
                    //tunnel1.secondTime = true;
                    playerBranch1.clear();
                    fader.fadeUp();
                }
                break;
                
            case E:
                //outroPlayer.draw();
                iss.draw();
                playerOutro.load(vids04);
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
                
            default:
                break;
        }
        mainGraphics.end();
        mainGraphics.draw(0,0);
    } else {
        introPlayer.drawPaused();
    }
    
    if (current_state==C && !tunnel1.secondTime) {
        ofPushMatrix();
        //ofSetColor(255, imgAlpha);
        ofSetColor(255, ofClamp(imgAlpha, 0, 255));
        ofTranslate(ofGetWidth()/2,ofGetHeight()/2,10);
        
        float d = tunnel1.camPos.z;
        if (d <= 17 && !timeFade) {
            imgAlpha = 255 - (d *15);
        } else if (d > 17 && !timeFade) {
            imgAlpha = 0;
        }
        
        if (!timeFade && exploreCounter <= 120) {
            exploreCounter++;
        } else {
            timeFade = true;
        }
            
        if (timeFade && imgAlpha > 0) {
            imgAlpha-=5;
        }
        
        //cout << exploreCounter << endl;
        
        explorePrompt.draw(-400,-200);
        //cout << "EXPLORE" << endl;
        ofSetColor(255, 255);
        ofPopMatrix();
        
        
    }
    
    
    
    
    //mainGraphics.draw(0,0);
    
    /*
    if (current_state != A && current_state != I) {
        introPlayer.drawPaused(isPaused);
    }
    */
    if (usingEEG && current_state != A && current_state != I && !isPaused) {
        vis.draw();
    }
    
    drawDebugMessages();
    //drawHelp();
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
    
    if (msg.message == lastMessage) {
        return;
    } else {
        lastMessage = msg.message;
    }
    
    if (ofIsStringInString(msg.message, "TunnelA")) {
        int branch = ofToInt(ofSplitString(msg.message, ":")[1]);
        int state = ofToInt(ofSplitString(msg.message, ":")[2]);
        cout << "Sent to Brancher from Tunnel A" << endl;
        ofLog(OF_LOG_NOTICE) << "##### Sent to Brancher from Tunnel A - " << ofGetElapsedTimeMillis() << " #####";
        brancher(1, branch, state);
    }
    
    if (ofIsStringInString(msg.message, "TunnelB")) {
        int branch = ofToInt(ofSplitString(msg.message, ":")[1]);
        int state = ofToInt(ofSplitString(msg.message, ":")[2]);
        cout << "Sent to Brancher from Tunnel B" << endl;
        ofLog(OF_LOG_NOTICE) << "##### Sent to Brancher from Tunnel B - " << ofGetElapsedTimeMillis() << " #####";
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
void controller::updateEegVis(float &f){
    //cout << "ping" << endl;
    if (mind.diff20() > -100 && !isPaused) {
        vis.update(mind.diff20());
    } else if (mind.diff10() > -100 && !isPaused) {
        vis.update(mind.diff10());
    }
}

//--------------------------------------------------------------
void controller::controlEvent(string &e){
    if (current_state == A && e == "start") {
        fader.moveOn();
    }
    
    if (e == "eegOn") {
        //cout << e << endl;
        if (!usingEEG) {
            mind.restart();
            usingEEG = true;
            cout << "started mindwave" << endl;
        }
    } else if (e == "eegOff") {
        //cout << e << endl;
        if (usingEEG) {
            mind.free();
            usingEEG = false;
            cout << "stopped mindwave" << endl;
        }
    } else if (e == "RESTART") {
        cout << "Restart" << endl;
        ofLog(OF_LOG_NOTICE) << "##### RESTARTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << " #####";
        sound.volume == 0;
        sound.newFile("audio/1.aiff");
        setup();
    }
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
#ifdef OF_DEBUG
            helpOn = !helpOn;
#endif
            break;
        
        case '0':
            tunnel1.toggleClipping();
            break;
            
        case '.':
            debugMessages = !debugMessages;
            break;
        /**************************************/
            
        case OF_KEY_ESC:
            if (current_state != A && current_state != I) {
                isPaused = !isPaused;
                sound.pause(isPaused);
            } else {
                isPaused = false;
            }
            break;
            
        case ';':
            if (current_state == I) {
                ofLog(OF_LOG_NOTICE) << "##### RESTARTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << " #####";
                sound.volume == 0;
                sound.newFile("audio/1.aiff");
                setup();
            }
            break;
            
        default:
            if (current_state == A) {
                //fader.moveOn();
            }
            break;
    }
}

//--------------------------------------------------------------
void controller::mousePressed(int x, int y, int button){
    if (current_state == A) {
        //fader.moveOn();
    }
}

//--------------------------------------------------------------
void controller::drawHelp(){
    ofSetColor(255);
    switch (current_state) {
        case B:
            if (helpOn) {
                ofDrawBitmapStringHighlight("There should be a MOVIE playing here. If there isn\'t, I\'m Sorry! Please let me know.\n\n"
                                            "If it does not automatically move on, or if it keeps looping, press \" 0 \" (zero)"
                                            , 20,20);
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
            }
            break;
            
        case D:
            if (helpOn) {
                ofDrawBitmapStringHighlight("There should be a MOVIE playing here. If there isn\'t, I\'m Sorry! Please let me know.\n\n"
                                            "If it does not automatically move on, or if it keeps looping, press \" 0 \" (zero)"
                                            , 20,20);
            }
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
        case I:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Mindwave Signal Quality: " + ofToString(mind.getSignalQuality()) + " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) + " | Solid Walls?: " + ofToString(tunnel1.isClipping),
                                   20,ofGetHeight() - 70);
            }
            break;
            
        case B:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Mindwave Signal Quality: " + ofToString(mind.getSignalQuality()) +  " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nWhich Movie: " + ofToString(playerIntro.whichMov) + " | Is playing? " + ofToString(playerIntro.isPlaying()) +
                                   " | Which File: " + playerIntro.getPath() + " | Solid Walls?: " + ofToString(tunnel1.isClipping),
                                   20,ofGetHeight() - 70);
            }
            break;
            
        case D:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Mindwave Signal Quality: " + ofToString(mind.getSignalQuality()) +  " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nWhich Movie: " + ofToString(playerBranch1.whichMov) + " | Is playing? " + ofToString(playerBranch1.isPlaying()) +
                                   " | Which File: " + playerBranch1.getPath() + " | Solid Walls?: " + ofToString(tunnel1.isClipping),
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
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Mindwave Signal Quality: " + ofToString(mind.getSignalQuality()) +  " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nWhich Movie: " + ofToString(playerOutro.whichMov) + " | Is playing? " + ofToString(playerOutro.isPlaying()) +
                                   " | Which File: " + playerOutro.getPath() + " | Solid Walls?: " + ofToString(tunnel1.isClipping),
                                   20,ofGetHeight() - 70);
            }
            break;
            
        case C:
            if (debugMessages) {
                ofDrawBitmapString("FrameRate: " + ofToString(ofGetFrameRate(),2) +
                                   " | Screen Size: " + ofToString(ofGetScreenWidth()) + "," + ofToString(ofGetScreenHeight()) +
                                   " | Window Size: " + ofToString(ofGetWidth()) + "," + ofToString(ofGetHeight()) +
                                   "\nEEG Has New Info: " + ofToString(mind.hasNewInfo()) + " | Mindwave Signal Quality: " + ofToString(mind.getSignalQuality()) +  " | Diff 20: " + ofToString(mind.diff20()) + " | Diff 10: " + ofToString(mind.diff10()) +
                                   "\nCamera Position: (" + ofToString(tunnel1.camera.getPosition().x,2) + "," +
                                   ofToString(tunnel1.camera.getPosition().y,2) + "," + ofToString(tunnel1.camera.getPosition().z,2) + ") | " +
                                   "Goal 1: (" + ofToString(tunnel1.goal1.x,2) + "," + ofToString(tunnel1.goal1.y,2) + "," + ofToString(tunnel1.goal1.z,2) + ") | " +
                                   "Goal 1 Distance: " + ofToString(tunnel1.camera.getPosition().squareDistance(tunnel1.goal1),2) +
                                   "\nGoal 2: (" + ofToString(tunnel1.goal2.x,2) + "," + ofToString(tunnel1.goal2.y,2) + "," + ofToString(tunnel1.goal2.z,2) + ") | " +
                                   " | Goal 2 Distance: " + ofToString(tunnel1.camera.getPosition().squareDistance(tunnel1.goal2),2) + " | Distance Factor: " +
                                   ofToString(tunnel1.distFactor,2) + " | Second Time? " + ofToString(tunnel1.secondTime) + " | Solid Walls?: " + ofToString(tunnel1.isClipping),
                                   20,ofGetHeight() - 70);
            }
            break;
            
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void controller::brancher(int source, int branch, int state){
    
    float diffThresh = 0.5;
    
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
        if (usingEEG && mind.hasNewInfo()) {
            if (mind.diff20() > -100.0) {
                if (mind.diff20()>diffThresh) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Attentive - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(0);
                } else if (mind.diff20()>0){
                    // SOMEWHAT Attentive
                    cout << "SOMEWHAT Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Attentive - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(1);
                } else if (mind.diff20()<-diffThresh) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Meditative - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(3);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Meditative - Branch 1 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(2);
                }
            } else if (mind.diff10() > -100.0) {
                if (mind.diff10()>diffThresh) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Attentive - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(0);
                } else if (mind.diff10()>0){
                    // SOMEWHAT Attentive
                    cout << "SOMEWHAT Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Attentive - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(1);
                } else if (mind.diff10()<-diffThresh) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Meditative - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(3);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Meditative - Branch 1 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerBranch1.setFile(2);
                }
            } else {
                // Cannot Determine
                cout << "Cannot Determine" << endl;
                ofLog(OF_LOG_NOTICE) << "##### Cannot Determine - Branch 1 - " << ofGetElapsedTimeMillis() << " #####";
                playerBranch1.setFile(branch);
            }
        } else {
            // NO EEG DATA
            cout << "NO EEG DATA" << endl;
            ofLog(OF_LOG_NOTICE) << "##### No EEG Data - Branch 1 - " << ofGetElapsedTimeMillis() << " #####";
            playerBranch1.setFile(branch);
        }
        
    } else if (source == 2){
        if (usingEEG && mind.hasNewInfo()) {
            if (mind.diff20() > -100.0) {
                if (mind.diff20()>diffThresh) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Attentive - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(0);
                } else if (mind.diff20()>0){
                    // SOMEWHAT Attentive
                    cout << "SOMEWHAT Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Attentive - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(0);
                } else if (mind.diff20()<-diffThresh) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Meditative - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(1);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Meditative - Branch 2 - Diff20 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(1);
                }
            } else if (mind.diff10() > -100.0) {
                if (mind.diff10()>diffThresh) {
                    // VERY Attentive
                    cout << "VERY Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Attentive - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(0);
                } else if (mind.diff10()>0){
                    // SOMEWHAT Attentive
                    cout << "Somewhat Attentive" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Attentive - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(0);
                } else if (mind.diff10()<-diffThresh) {
                    //VERY Meditative
                    cout << "VERY Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Very Meditative - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(1);
                } else {
                    //Somewhat Meditative
                    cout << "Somewhat Meditative" << endl;
                    ofLog(OF_LOG_NOTICE) << "##### Somewhat Meditative - Branch 2 - Diff10 - " << ofGetElapsedTimeMillis() << " #####";
                    playerOutro.setFile(1);
                }
            } else {
                // Cannot Determine
                cout << "Cannot Determine" << endl;
                ofLog(OF_LOG_NOTICE) << "##### Cannot Determine - Branch 2 - " << ofGetElapsedTimeMillis() << " #####";
                playerOutro.setFile(floor(ofRandom(2)));
            }
        } else {
            // NO EEG DATA
            cout << "NO EEG DATA" << endl;
            ofLog(OF_LOG_NOTICE) << "##### No EEG Data - Branch 2 - " << ofGetElapsedTimeMillis() << " #####";
            playerOutro.setFile(floor(ofRandom(2)));
        }
    }
    
    fader.moveOn();
    
}

//--------------------------------------------------------------
void controller::exit(){
    mind.free();
    ofLog(OF_LOG_NOTICE) << "##### QUITTING - " << ofGetTimestampString("%B %e, %Y %h:%M:%S %a - ") << ofGetElapsedTimeMillis() << " #####";
    cout << "Axion is quitting..." << endl;
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
