#include "intro.h"


//--------------------------------------------------------------
Intro::Intro(){
    setup();
}

Intro::~Intro(){
    //cout << "I'm dead" << endl;
}

//--------------------------------------------------------------
void Intro::setup(){
    if(initialized) {
        return;
    }
    firstTime = true;
    counter = 0;
    firstAlpha = 0;
    initialized = true;
    
    introImg.loadImage("logo.png");
    pointer.loadImage("pointer.png");
    introModel.loadModel("introMesh.obj");
    introModel.setPosition(1920/2, 1080/2, 0);
    
    canvas.allocate(1920, 1080, GL_RGBA);
    canvas.begin();
    ofClear(255,255,255, 0);
    canvas.end();
    
    introState = A;
    introFader.fadeUp();
}

//--------------------------------------------------------------
void Intro::update(){
    introModel.update();
    introMesh = introModel.getCurrentAnimatedMesh(0);
    introModel.setPosition(1920/2, 1080/2, 0);
    
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
    
    
    
    
    
    pointer.draw(ofGetMouseX(), ofGetMouseY(), 35, 35);
    introFader.draw();
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



