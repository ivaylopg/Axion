#include "eegVisLine.h"

//--------------------------------------------------------------
visLine::visLine(){
    interpolationType = msa::kInterpolationCubic;
    useLength = false;
    spline2D.reserve(8);
    numSteps = 8 * 4;
    
    mapped.clear();
    for (int i = 0; i < 10; i++) {
        mapped.push_back(0.0);
    }
}

//--------------------------------------------------------------
void visLine::update() {
}