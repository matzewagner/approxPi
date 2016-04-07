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
    // Get latest approximation:
    float latest_approximation = approximator.currentApprox;

    // write to frame buffer object
    fbo.begin();
    ofClear(0, 0, 0, 0);
    drawDigits(latest_approximation);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for(int i = 0; i < bufferSize * nChannels; i += nChannels) {
        //TODO: Playback 6 channel file. 
        //TODO: Account for sampledroppping for other channels. 

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
    fbo.draw(0,0);

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

//--------------------------------------------------------------
void ofApp::drawDigits(float number){
    // draw the digits
    string digits = numberToString(number);

    //TODO: port this function from liveAudio brach
}