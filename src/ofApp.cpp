#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    phase = 0;
    ofSoundStreamSetup(8, 0); // 2 output channels (stereo), 0 input channels
    audioPlayer.load("ApproximatingPi_8channel.wav");
    if(audioPlayer.isLoaded())
    {
        audioPlayer.play();
    }
    else
    {
        std::cout << "Soundfile Not Loaded GET IT TOGETHER" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for(int i = 0; i < bufferSize * nChannels; i += nChannels) {
        // float sample = sin(phase); // generating a sine wave sample
        // output[i] = sample; // writing to the left channel
        // output[i+1] = sample; // writing to the right channel
        // phase += 0.05;

        approximator.tick(); // A sample-accurate tick
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    if(audioPlayer.isLoaded())
    {
        audioPlayer.stop();
        audioPlayer.unload();        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Get latest approximation:
    float latest_approximation = approximator.currentApprox;
    string number = numberToString(latest_approximation);

    // TODO: Draw it on multiple screens.
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