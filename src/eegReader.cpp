#include "eegReader.h"

//--------------------------------------------------------------
EEGreader::EEGreader(){
	setup();
}

//--------------------------------------------------------------
void EEGreader::setup(){
    if(initialized) {
		return;
	}
	initialized = true;
    
    thinkGear.setup();
    ofAddListener(thinkGear.blinkChangeEvent, this, &EEGreader::blinkListener);
    
    interpolationType = msa::kInterpolationCubic;
    useLength = false;
    spline2D.reserve(8);
    numSteps = 8 * 4;
    
    ave3s = 0.0;
    ave10s = 0.0;
    ave20s = 0.0;
    diff10s = 0.0;
    diff20s = 0.0;
    hasD10 = false;
    hasD20 = false;
    
    for (int i=0; i < 10; i++) {
        values[i] = 0.0;
        mapped[i] = 0.0;
        averages[i] = 0.0;
        loHi[i][0] = 100000.0;
        loHi[i][1] = 1.0;
    }
    
    numBlinks = 0;
    lastBlinkVal = 0;
}

//--------------------------------------------------------------
void EEGreader::reset(){
    ave3s = 0.0;
    ave10s = 0.0;
    ave20s = 0.0;
    diff10s = 0.0;
    diff20s = 0.0;
    attMedRatio.clear();
    hasD10 = false;
    hasD20 = false;
}

//--------------------------------------------------------------
void EEGreader::update(){
    /*
     values array is:
     
     values[0] is TG_DATA_ATTENTION = 2;
     values[1] is TG_DATA_MEDITATION = 3;
     values[2] is TG_DATA_DELTA = 5;
     values[3] is TG_DATA_THETA = 6;
     values[4] is TG_DATA_ALPHA1 = 7;
     values[5] is TG_DATA_ALPHA2 = 8;
     values[6] is TG_DATA_BETA1 = 9;
     values[7] is TG_DATA_BETA2 = 10;
     values[8] is TG_DATA_GAMMA1 = 11;
     values[9] is TG_DATA_GAMMA2 = 12;
     */
    
    //thinkGear.update();
    if (thinkGear.ableToConnect) {
        if (ofGetFrameNum()%60 == 0) {
            
            thinkGear.update();
            
            if (thinkGear.getSignalQuality() == 0 && thinkGear.getNewInfo()) {
                for (int i=0; i<10; i++) {
                    values[i] = thinkGear.values[i];
                    if (values[1] == 0) {
                        values[1] = 0.0001;     // To prevent divide by zero
                    }
                    
                    if (i > 1) {
                        // Update Min & Max
                        if (values[i] < loHi[i][0]) {
                            loHi[i][0] = values[i];
                            if (loHi[i][0] == 0) {
                                loHi[i][0] = 0.001;
                            }
                        }
                        if (values[i] > loHi[i][1]) {
                            loHi[i][1] = values[i];
                        }
                        if (loHi[i][0] == loHi[i][1]) {
                            loHi[i][1]+=0.1;
                        }
                        
                        //Update mapped Values
                        mapped[i] = ofMap(values[i], loHi[i][0], loHi[i][1], 0, 100);
                    } else {
                        mapped[i] = values[i];
                    }
                }
                
                // Update attention
                for (int i=0; i < atts.size(); i++) {
                    atts[i].x-=32;
                }
                if (atts.size()>32) {
                    atts.erase(atts.begin());
                }
                ofVec2f vA = ofVec2f(ofGetWidth(),values[0]);
                atts.push_back(vA);
                
                
                // Update meditation
                for (int i=0; i < meds.size(); i++) {
                    meds[i].x-=32;
                }
                if (meds.size()>32) {
                    meds.erase(meds.begin());
                }
                ofVec2f vM = ofVec2f(ofGetWidth(),values[1]);
                meds.push_back(vM);
                
                float ave = values[0]/values[1];
                attMedRatio.push_back(ave);
                
                //cout << values[0] << "/" << values[1] << " : " << values[0]/values[1] << " : " << thinkGear.getIsConnected() << " : " << thinkGear.getSignalQuality() << endl;
                cout << "Diff 10: " << diff10() << " | Diff 20:" << diff20() << endl;
                
            } else if (!thinkGear.getNewInfo()){
                //cout << "bad connection" << endl;
            }
        }
        
        
        while (attMedRatio.size()>20) {
            attMedRatio.erase(attMedRatio.begin());
        }
        
        
        if (attMedRatio.size()>3) {
            float tot3s = 0;
            for (int i = attMedRatio.size()-1; i >= attMedRatio.size()-3; i--) {
                tot3s+=attMedRatio[i];
            }
            ave3s = tot3s/3;
        }
        
        if (attMedRatio.size()>10) {
            float tot10s = 0;
            for (int i = attMedRatio.size()-1; i >= attMedRatio.size()-10; i--) {
                tot10s+=attMedRatio[i];
            }
            ave10s = tot10s/10;
            diff10s = ave3s-ave10s;
            hasD10 = true;
        }
        
        if (attMedRatio.size()==20) {
            float tot20s = 0;
            for (int i = 0; i < attMedRatio.size(); i++) {
                tot20s+=attMedRatio[i];
                //cout << i << endl;
            }
            ave20s = tot20s/20;
            diff20s = ave3s-ave20s;
            hasD20 = true;
            //cout << "--- " << diff20s << " ---" <<endl;
        }
    }
    
}

//--------------------------------------------------------------
float EEGreader::diff10(){
    if (hasD10) {
        return diff10s;
    } else {
        return -100.0;
    }
}

//--------------------------------------------------------------
float EEGreader::diff20(){
    if (hasD20) {
        return diff20s;
    } else {
        return -100.0;
    }
}

//--------------------------------------------------------------
bool EEGreader::hasNewInfo(){
    return thinkGear.getNewInfo();
}

//--------------------------------------------------------------
void EEGreader::draw(){

}

//--------------------------------------------------------------
void EEGreader::blinkListener(float &param)
{
    numBlinks++;
    lastBlinkVal = param;
    //cout << param << endl;
}

//--------------------------------------------------------------
void EEGreader::free(){
    thinkGear.freeConnection();
}