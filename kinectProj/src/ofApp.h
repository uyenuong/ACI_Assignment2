#pragma once

#include "ofMain.h"
#include "ofxOpenNI.h"
#include "timedRectangle.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
private:
    
    void handEvent(ofxOpenNIHandEvent & event);
    
    // Kinect device
    ofxOpenNI openNIDevice;
    
    // Storing drawn rectangles
    deque<TimedRectangle> rects;
    int clearRectangles();
    
    // Foreground image
    ofImage foreground;
    
    // Frame buffers to create alpha mask
    ofFbo maskFbo;
    ofFbo fbo;
    
    // Shader to composite the images together using the mask
    ofShader shader;
		
};
