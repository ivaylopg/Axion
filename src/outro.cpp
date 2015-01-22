#include "outro.h"


//--------------------------------------------------------------
Outro::Outro(){
	setup();
}


//--------------------------------------------------------------
void Outro::setup(){
    if(initialized) {
		return;
	}
    
	initialized = true;
    
    outImage.loadImage("logo.png");
    ofTrueTypeFont::setGlobalDpi(72);
    akzidenz32.loadFont("akzidenz-grotesk-light.ttf", 32,true,true);
    akzidenz28.loadFont("akzidenz-grotesk-light.ttf", 28,true,true);
    akzidenzS.loadFont("akzidenz-grotesk-light.ttf", 18,true,true);
    //akzidenz.setLineHeight(18.0f);
	akzidenz32.setLetterSpacing(1.037);
    akzidenz28.setLetterSpacing(1.05);
    akzidenz28.setLineHeight(30);
    pointer.loadImage("pointer.png");
    restartButton.setup(&akzidenzS, "RESTART");
    
    scroll = 1600;
}


//--------------------------------------------------------------
void Outro::update(){
    scroll -= 1.0f;
    cout << scroll << endl;
    if (scroll < -1800) {
        scroll = 1600;
    }
}

//--------------------------------------------------------------
void Outro::draw(){
    float scl = (float) ofGetWidth() / (float) ofGetScreenWidth();
    ofBackground(0);
    ofSetColor(255);
    int imgW = (int) ceil(ofGetWidth()/7);
    int imgH = (int) ceil((imgW * outImage.height)/outImage.width);
    ofPushMatrix();
    ofTranslate(3 * ofGetWidth()/4, 50, -1);
    outImage.draw(0, 0, imgW, imgH);
    ofPopMatrix();
    
    ofPushMatrix();
    float textScale = ofGetWidth()/2560.0;
    ofTranslate(0,0,-1);
    ofScale(textScale, textScale);
    
    ofSetColor(255);
    akzidenz32.drawString("CREATORS:", 100, 100+scroll);
    
    ofSetColor(128);
    akzidenz28.drawString("RAIN ASHFORD, IVAYLO GETOV, KYLE GUSTAFSON,\nJASMINE IDUN LYMAN, JULIAN MACIEJEWSKI, JASON WISHNOW", 100, 140+scroll);
    
    akzidenz28.drawString("RAIN ASHFORD\nIVAYLO GETOV\nKYLE GUSTAFSON\nJASMINE IDUN LYMAN\nJULIAN MACIEJEWSKI\nJASON WISHNOW", 100, 300+scroll);
    
    ofSetColor(255);
    akzidenz28.drawString("INTERACTIVITY DEVELOPMENT\nSOFTWARE & VISUAL DESIGN\nSCIENCE ADVISOR\nEXPERIENCE DESIGN\nSOFTWARE DEVELOPMENT\nCREATIVE DEVELOPMENT", 450, 300+scroll);
    
    ofSetColor(255);
    akzidenz32.drawString("SCIENTISTS:", 100, 580+scroll);
    ofSetColor(128);
    akzidenz28.drawString("PROFESSOR MARTIN POHL"
                          "\n\n\nDR. MARK WYMAN"
                          "\n\n\nPROFESSOR ELENA APRILE"
                          "\n\n\nDR. SARAH MILLER"
                          "\n\n\nDR. JENNIFER SIEGAL-GASKINS"
                          "\n\n\nDR. JASON RHODES"
                          "\n\n\nDR. ALINA KIESSLING"
                          "\n\n\nDR. SEAN CARROLL", 100, 620+scroll);
    
    ofSetColor(255);
    akzidenz28.drawString("\nDIRECTOR of the NUCLEAR and PARTICLE PHYSICS DEPARTMENT, UNIVERSITY OF GENEVA"
                          "\n\n\nAMES ARTHUR POSTDOCTORAL FELLOW, NYU"
                          "\n\n\nCO-DIRECTOR, COLUMBIA ASTROPHYSICS LABORATORY, COLUMBIA UNIVERSITY"
                          "\n\n\nCHANCELLOR’S ADVANCE FELLOW AND McCUE FELLOW, UNIVERSITY OF CALIFORNIA, IRVINE"
                          "\n\n\nEINSTEIN POSTDOCTORAL FELLOW, CALTECH"
                          "\n\n\nSCIENTIST AT JET PROPULSION LABS; U.S. SCIENCE LEAD FOR ESA'S EUCLID MISSION"
                          "\n\n\nJPOSTDOCTORAL FELLOW AT JET PROPULSION LABS"
                          "\n\n\nSENIOR RESEARCH ASSOCIATE IN PHYSICS, CALTECH", 100, 620+scroll);
    
    
    ofSetColor(255);
    akzidenz32.drawString("SOUNDSCAPE:", 100, 1400+scroll);
    ofSetColor(128);
    akzidenz28.drawString("ALAIN THIBAULT\n"
                          "IDA LONG\n"
                          "IDUN", 100, 1440+scroll);
    
    
    ofSetColor(255);
    akzidenz32.drawString("THANK YOU:", 100, 1600+scroll);
    ofSetColor(128);
    akzidenz28.drawString("NEAL HARTMAN at CERN; OPEYEMI OLUKEMI, INGRID KOPP, and AMELIE LEENHARDT at TRIBECA FILM INSTITUTE\n"
                          "NATASHA RODRIGUEZ-BACCHUS ( DESIGN), MACIEJ MUSZKOWSKI (PROGRAMMING), ZACH CALDWELL (VIDEOGRAPHY)\n"
                          "JEREMY UNGAR, NICK ZEIG-OWENS, and CLINT JOSEPH HANAWAY (CAMERA ASSISTANTS)\n"
                          "INSTITUTION OF NEUROSCIENCE AND PHYSIOLOGY IN GOTHENBURG (AUDIO)\n"
                          "JOONA KURIKKA at the CERN IDEALAB, and EVERYBODY AT CERN, CINEGLOBE, AND TFI.", 100, 1640+scroll);
    
    
    ofPopMatrix();
    
    restartButton.draw((3 * (ofGetWidth()/4)) + (imgW * 0.09), 50 + imgH * 1.1);
    
    
    pointer.draw(ofGetMouseX(), ofGetMouseY(), 35, 35);
}

void Outro::resetScroll() {
    scroll = 1600;
}