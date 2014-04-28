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
    //akzidenz.setLineHeight(18.0f);
	akzidenz32.setLetterSpacing(1.037);
    akzidenz28.setLetterSpacing(1.05);
    akzidenz28.setLineHeight(30);
}


//--------------------------------------------------------------
void Outro::update(){
}

//--------------------------------------------------------------
void Outro::draw(){
    float scl = (float) ofGetWidth() / (float) ofGetScreenWidth();
    ofBackground(0);
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(3 * ofGetWidth()/4, ofGetHeight()/6);
    ofScale(scl*0.6, scl*0.6);
    ofTranslate(-outImage.width/2, 0);
    outImage.draw(0, 0);
    ofPopMatrix();
    
    ofPushMatrix();
    float textScale = ofGetWidth()/2560.0;
    ofScale(textScale, textScale);
    
    ofSetColor(255);
    akzidenz32.drawString("CREATORS:", 100, 300);
    
    ofSetColor(128);
    akzidenz28.drawString("RAIN ASHFORD, IVAYLO GETOV, KYLE GUSTAFSON,\nJASMINE IDUN LYMAN, JULIAN MACIEJEWSKI, JASON WISHNOW", 100, 340);
    
    akzidenz28.drawString("RAIN ASHFORD\nIVAYLO GETOV\nKYLE GUSTAFSON\nJASMINE IDUN LYMAN\nJULIAN MACIEJEWSKI\nJASON WISHNOW", 100, 500);
    
    ofSetColor(255);
    akzidenz28.drawString("INTERACTIVITY DEVELOPER\nSOFTWARE & GRAPHICS\nSCIENCE ADVISOR\nEXPERIENCE DESIGNER\nSOFTWARE DEVELOPER\nCREATIVE DEVELOPER", 450, 500);
    
    ofSetColor(255);
    akzidenz32.drawString("SCIENTISTS:", 100, 780);
    ofSetColor(128);
    akzidenz28.drawString("PROFESSOR MARTIN POHL"
                          "\n\n\nDR. MARK WYMAN"
                          "\n\n\nPROFESSOR ELENA APRILE", 100, 820);
    
    ofSetColor(255);
    akzidenz28.drawString("\nDIRECTOR of the NUCLEAR and PARTICLE PHYSICS DEPARTMENT, UNIVERSITY OF GENEVA"
                          "\n\n\nJAMES ARTHUR POSTDOCTORAL FELLOW, NYU"
                          "\n\n\nCO-DIRECTOR, COLUMBIA ASTROPHYSICS LABORATORY, COLUMBIA UNIVERSITY", 100, 820);
    
    
    ofSetColor(255);
    akzidenz32.drawString("THANK YOU:", 100, 1120);
    ofSetColor(128);
    akzidenz28.drawString("NEAL HARTMAN at CERN; OPEYEMI OLUKEMI, INGRID KOPP, and AMELIE LEENHARDT at TRIBECA FILM INSTITUTE\n"
                          "NATASHA RODRIGUEZ-BACCHUS (LOGO DESIGN), MACIEJ MUSZKOWSKI (PROGRAMMING HELP), ZACH CALDWELL (VIDEOGRAPHY)\n"
                          "JOONA KURIKKA at the CERN IDEALAB, and EVERYBODY AT CERN, CINEGLOBE, AND TFI.", 100, 1160);
    
    
    ofPopMatrix();
}