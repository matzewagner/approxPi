#include "ofApp.h"
#include <String>
#include <sstream>
#include <iomanip>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30, 30, 30);
    fontSize = int(ofGetHeight()*0.25);
    myFont.load("Futura-Medium.ttf", fontSize);

    ofSoundStreamSetup(2, 0);
    for (int i=0; i<NUM_PARTIALS; ++i) {
        phase[i] = 0;
        phaseIncrement[i] = freq*(i+1)*TABLE_SIZE / sr;
    }
    // fill table with square wave
    for (int j=0; j<TABLE_SIZE; ++j) {
        for (int i=1; i<21; i+=2) {
            sinBuf[j] += sin((float(j)/float(TABLE_SIZE))*2*i*M_PI)*(1.0/(i+1))*0.5;
        }

    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // convert nyNumber into 3 substrings
    s << std::fixed << std::setprecision(10) << myNumber*4.0;
    myPreString = s.str();
    
    myString1 = myPreString.substr(0, 4);
    myString2 = myPreString.substr(4, 3);
    myString3 = myPreString.substr(7, 4);
    
    // get width of strings
    sWidth1 = myFont.getStringBoundingBox(myString1, ofGetWidth()*0.5, ofGetHeight()*0.3).getWidth();
    sWidth2 = myFont.getStringBoundingBox(myString2, ofGetWidth()*0.5, ofGetHeight()*0.625).getWidth();
    sWidth3 = myFont.getStringBoundingBox(myString3, ofGetWidth()*0.5, ofGetHeight()*0.95).getWidth();
    
    // draw strings
    ofSetColor(200, 180, 100);
    myFont.drawString(myString1, ofGetWidth()*0.5 - sWidth1*0.5, ofGetHeight()*0.3);
    myFont.drawString(myString2, ofGetWidth()*0.5 - sWidth2*0.5, ofGetHeight()*0.625);
    myFont.drawString(myString3, ofGetWidth()*0.5 - sWidth3*0.5, ofGetHeight()*0.95);
    
    // clear stringstream
    s.str("");
    s.clear();
    
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

//--------------------------------------------------------------
double ofApp::approxPi(double prev_value, int n) {
    sign *= -1;
    return prev_value + sign/double(n);
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    string thisAmp;
    // approximate pi
    timeNow = ofGetElapsedTimeMillis();
    if (fmod(timeNow, updateDeltaTime) < 5) {
        myNumber = approxPi(myNumber, n);
        
//        printToConsole();
        
        // extract partial amplitudes
        partialAmp[0] = stoi(myPreString.substr(0,1));
        for (int i=2; i<NUM_PARTIALS; ++i) {
            partialAmp[i] = stoi(myPreString.substr(i,1));
        }
        ++iteration;
        n+=2;
        ofResetElapsedTimeCounter();
    }
    
    for (int i=0; i<bufferSize*nChannels; i+=2) {
        for (int j=0; j<NUM_PARTIALS; ++j) {
            while (phase[j] >= TABLE_SIZE) {
                phase[j] -= TABLE_SIZE;
            }
            while (phase[j] < 0) {
                phase[j] += TABLE_SIZE;
            }
            
            float sample = sinBuf[int(phase[j])]*partialAmp[j];
            output[i] += sample;
            output[i+1] += sample;
            phase[j] += phaseIncrement[j];
        }
    }
}

//--------------------------------------------------------------
void ofApp::printToConsole() {
    std::cout
        << "Iteration: " << iteration
        << "\tValue: " << myNumber*4.0
        << "\tupdate frequency: " << double(1000.0/ timeNow) << " Hz"
        << std::endl;
}
