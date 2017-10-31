//
//  timedRectangle.hpp
//  kinectProj
//
//  Created by Uyen Uong on 10/31/17.
//

#ifndef timedRectangle_hpp
#define timedRectangle_hpp

#include <stdio.h>
#include "ofMain.h"

class TimedRectangle : public ofRectangle {
public:
    TimedRectangle();
    TimedRectangle(float x, float y, float w, float h);
    
    float getTimeCreated() { return timeCreated; }
    
private:
    float timeCreated;
};

#endif /* timedRectangle_hpp */
