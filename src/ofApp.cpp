#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    phase = 0;
    current_sample = 0;
    ofSoundStreamSetup(2, 0); // 2 output channels (stereo), 0 input channels

}

//--------------------------------------------------------------
void ofApp::update(){

    cout << approximator.currentApprox << endl;
    cout << current_sample << " " << approximator.currentSample << endl << endl;

}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for(int i = 0; i < bufferSize * nChannels; i += nChannels) {
        float sample = sin(phase); // generating a sine wave sample
        output[i] = sample; // writing to the left channel
        output[i+1] = sample; // writing to the right channel
        phase += 0.05;
        approximator.tick();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

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