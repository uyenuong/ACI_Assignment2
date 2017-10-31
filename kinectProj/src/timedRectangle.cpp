//
//  timedRectangle.cpp
//  kinectProj
//
//  Created by Uyen Uong on 10/31/17.
//

#include "timedRectangle.hpp"

TimedRectangle::TimedRectangle() : ofRectangle() {
    timeCreated = ofGetElapsedTimef();
}

TimedRectangle::TimedRectangle(float x, float y, float w, float h) : ofRectangle(x, y, w, h) {
    timeCreated = ofGetElapsedTimef();
}
