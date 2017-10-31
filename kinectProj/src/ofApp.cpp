#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(640, 480);
    
    // load shader
    shader.load("shadersGL2/shader");
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // Setup Kinect
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    
    // setup the hand generator
    openNIDevice.addHandsGenerator();
    
    // add all focus gestures (ie., wave, click, raise arm)
    openNIDevice.addAllHandFocusGestures();
    
    openNIDevice.setMaxNumHands(4);
    
    openNIDevice.start();
    
    // Load foreground image
    foreground.load("raindrops-window.jpeg");
    foreground.setImageType(OF_IMAGE_COLOR_ALPHA);
    
    // allocate space for the frame buffers
    maskFbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    // Clear the FBO's
    // otherwise it will bring some junk with it from the memory
    maskFbo.begin();
    ofClear(0,0,0,255);
    maskFbo.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){
    openNIDevice.update();
    
    // get number of current hands
    int numHands = openNIDevice.getNumTrackedHands();
    
    // iterate through the identified hands
    for (int i = 0; i < numHands; i++){
        
        // get a reference to this user
        ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);
        
        // get hand position
        ofPoint & handPosition = hand.getPosition();
        // do something with the positions like:
        
        // create a rect at the position
        TimedRectangle r = TimedRectangle(handPosition.x, handPosition.y, 40, 40);
        rects.push_back(r);
        
    }
}

//--------------------------------------------------------------
int ofApp::clearRectangles() {
    // Get rid of rectangle after 3 seconds
    while (!rects.empty() && (ofGetElapsedTimef() - rects[0].getTimeCreated()) > 3 ) {
        rects.pop_front();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(255, 255, 255);
    
    //----------------------------------------------------------
    // this is our alpha mask which we draw into.
    maskFbo.begin();
    
    // Clear mask each time draw on it, so that the line disappears
    ofClear(0,0,0,255);
    
    // draw the rectangles
    clearRectangles();
    for (int i = 0; i < rects.size(); i++) {
        ofDrawRectangle(rects[i]);
    }
    
    maskFbo.end();
    
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    
    //----------------------------------------------------------
    // HERE the shader-masking happens
    fbo.begin();
    // Cleaning everthing with alpha mask on 0 in order to make it transparent by default
    ofClear(0, 0, 0, 0);
    
    shader.begin();
    // here is where the fbo is passed to the shader
    shader.setUniformTexture("maskTex", maskFbo.getTexture(), 1 );
    
    // Draw the background which is what the camera sees
    openNIDevice.drawImage();
    
    shader.end();
    fbo.end();
    
    //----------------------------------------------------------
    // FIRST draw the foreground image
//    ofEnableAlphaBlending();
//    ofSetColor(255,255,255,100);
    foreground.draw(0,0);
//    ofDisableAlphaBlending();
    
    // THEN draw the masked fbo on top
    fbo.draw(0,0);
//    ofEnableAlphaBlending();
//    ofSetColor(255,255,255,100);
//    fbo.getTexture().draw(0,0);
//    ofDisableAlphaBlending();
    
    glDisable(GL_BLEND);
}

//--------------------------------------------------------------
void ofApp::handEvent(ofxOpenNIHandEvent & event){
    // show hand event messages in the console
    ofLogNotice() << getHandStatusAsString(event.handStatus) << "for hand" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void ofApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
