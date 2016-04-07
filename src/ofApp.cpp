#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fontSize = 80;
    myFont.load("Futura-Medium.ttf", fontSize);
    fbo.allocate(450, 450);

    ofSoundStreamSetup(6, 0); // 6 output channels (stereo), 0 input channels
    ofSoundStreamStart();
}

//--------------------------------------------------------------
void ofApp::update(){
    // Get latest approximation:
    float latest_approximation = approximator.currentApprox;

    ofSetBackgroundColor(BGColor, BGColor, BGColor);


    // write to frame buffer object
    fbo.begin();
    ofClear(0, 0, 0, 0);
    drawDigits(latest_approximation);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for(int i = 0; i < bufferSize * nChannels; i += nChannels) {

        approximator.tick(); // A sample-accurate approximator tick
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);

    // TODO: Draw it on multiple screens.
}

//--------------------------------------------------------------
void ofApp::drawDigits(float number){
    int* digits = getDigits(number);    // Get the digits

    int lineIndex = 0;
    int place = 1;
    
    for(int i=0; i<APPROXIMATOR_PRECISION; i++)
    {
        float colorScaler;

        // Also draw the dot here
        if(i==1)
        {
            colorScaler = 1.0;
            ofSetColor(255*colorScaler, 180*colorScaler, 100*colorScaler);
            myFont.drawString(".", place*fontSize*0.8, ofGetHeight()*lineSpacing[lineIndex]);
            ++place;
        }

        colorScaler = digits[i];
        ofSetColor(255*colorScaler, 180*colorScaler, 100*colorScaler);
        myFont.drawString(to_string(digits[i]), place*fontSize*0.8, ofGetHeight()*lineSpacing[lineIndex]);
        ++place;
        if (i == 3 || i == 6) 
        {
            ++lineIndex;
            place = 1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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