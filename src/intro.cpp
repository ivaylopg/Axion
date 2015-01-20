#include "intro.h"


//--------------------------------------------------------------
Intro::Intro(){
    setup();
}

Intro::~Intro(){
    //cout << "I'm dead" << endl;
    ofUnregisterMouseEvents(this);
}

//--------------------------------------------------------------
void Intro::setup(){
    
    introImg.loadImage("logo.png");
    pointer.loadImage("pointer.png");
    introModel.loadModel("introMesh.obj");
    introModel.setPosition(1920/2, 1080/2, 0);
    
    canvas.allocate(1920, 1080, GL_RGBA);
    canvas.begin();
    ofClear(255,255,255, 0);
    canvas.end();
    
    introState = A;
    readyToMove = false;
    //introFader.fadeUp();
    
    woodenBox.setup("audio/woodenBoxLoop.aiff");
    woodenBox.jumpToVolume(1.0);
    woodenBox.pause(true);
    
    
    ofAddListener(introFader.curtainDrawn, this, &Intro::faderDone);
    ofRegisterMouseEvents(this);
}

//--------------------------------------------------------------
void Intro::update(){
    introModel.update();
    introMesh = introModel.getCurrentAnimatedMesh(0);
    introModel.setPosition(1920/2, 1080/2, 0);
    
    woodenBox.update();
    introFader.update();
    drawCanvas();
}

//--------------------------------------------------------------
void Intro::drawCanvas(){
    
    canvas.begin();
    ofBackground(0);
    
    ofSetColor(255);
    float scl = (float) 1920 / (float) ofGetScreenWidth();
    float imgW = ceil(1920/10);
    float imgH = ceil((imgW * introImg.height)/introImg.width);
    float transX = 1920/6;
    float transY = 1080/10;
    
    //ofBackgroundGradient(ofColor(20,20,20),ofColor(0,0,0), OF_GRADIENT_CIRCULAR);
    
    
    switch (introState) {
        case A: {
            ofPushMatrix();
            ofTranslate(1920/2, 1080/2,-1);
            imgW *= 1.0 + (float)(counter/(3000.0));
            imgH *= 1.0 + (float)(counter/(3000.0));
            introImg.draw(0-imgW/2, 0-imgH/2, imgW, imgH);
            if (counter < 20 * ofGetFrameRate()) {
                counter++;
            }
            ofPopMatrix();
            break;
        }
            
        case B: {
            woodenBox.play();
            introLight.enable();
            ofSetColor(255, 255);
            
            ofPushMatrix();
            ofTranslate((1920/2)*0.3, (1080/2)*0.3, 300);
            ofTranslate(introModel.getPosition().x, introModel.getPosition().y, 0);
            
            ofRotateX(10);
            ofRotateZ(-20);
            ofRotateY(introRot);
            introRot+=0.05;
            
            ofTranslate(-introModel.getPosition().x, -introModel.getPosition().y, 0);
            
            ofxAssimpMeshHelper & meshHelper = introModel.getMeshHelper(0);
            ofMultMatrix(introModel.getModelMatrix());
            ofMultMatrix(meshHelper.matrix);
            
            ofScale(scl, scl);
            //introMesh.drawFaces();
            introMesh.drawWireframe();
            
            ofPopMatrix();
            introLight.disable();
            ofDisableLighting();
            break;
        }
            
        default:
            break;
    }
    
    
    
    float px = (float) ofGetMouseX() * 1920 / ofGetWidth() ;
    float py = (float) ofGetMouseY() * 1080 /ofGetHeight();
    
//    cout << px << " | " << py << endl;
    
    //float px = ofGetMouseX();
    //float py = ofGetMouseY();
    
    pointer.draw(px, py, 35, 35);
    introFader.draw(canvas.getWidth(),canvas.getHeight());
    canvas.end();
}

//--------------------------------------------------------------
void Intro::draw(){
    draw(ofGetWidth(),ofGetHeight());
    
}

//--------------------------------------------------------------
void Intro::draw(float w, float h){
    canvas.draw(0,0,w,h);
}

//--------------------------------------------------------------
void Intro::faderDone(float & f) {
    //cout << f << endl;
    switch (introState) {
        case A:
            if (readyToMove) {
                introState = B;
                readyToMove = false;
                introFader.addDelay(-30);
            }
            break;
            
        case B:{
            string s = "test";
            ofNotifyEvent(sendMessage, s);
            break;
            }
            
        default:
            break;
    }
}

void Intro::mouseMoved(ofMouseEventArgs & args){}
void Intro::mouseDragged(ofMouseEventArgs & args){}
void Intro::mousePressed(ofMouseEventArgs & args){}
void Intro::mouseReleased(ofMouseEventArgs & args){
    if (introState == A || introState == B) {
        introFader.fadeUp();
        readyToMove = true;
    }
}



