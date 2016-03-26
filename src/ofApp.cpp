#include "ofApp.h"
#include <String>
#include <sstream>
#include <iomanip>

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(0, 0, 0);
    fontSize = int(ofGetHeight()*0.25);
    myFont.load("Futura-Medium.ttf", fontSize);
    windowIndexFont.load("Futura-Medium.ttf", 16);

    fbo.allocate(450, 450);
    
    ofSoundStreamSetup(2, 0);
    // set values for incrementing the different partials
    for (int i=0; i<NUM_PARTIALS; ++i) {
        phase[i] = 0;
        phaseIncrement[i] = freq*(i+1)*TABLE_SIZE / sr;
    }
    // fill table with square wave
    for (int j=0; j<TABLE_SIZE; ++j) {
        for (int i=1; i<21; i+=2) {
            sinBuf[j] += sin((float(j)/float(TABLE_SIZE))*2*i*M_PI)*(1.0/i)*0.5;
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::setupW2() {
    ofBackground(BGColor, BGColor, BGColor);
}

//--------------------------------------------------------------
void ofApp::setupW3() {
    ofBackground(BGColor, BGColor, BGColor);
}

//--------------------------------------------------------------
void ofApp::setupW4() {
    ofBackground(BGColor, BGColor, BGColor);
}

//--------------------------------------------------------------
void ofApp::setupW5() {
    ofBackground(BGColor, BGColor, BGColor);
}

//--------------------------------------------------------------
void ofApp::setupW6() {
    ofBackground(BGColor, BGColor, BGColor);
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSetBackgroundColor(BGColor, BGColor, BGColor);
    
    // convert nyNumber into 3 substrings
    s << std::fixed << std::setprecision(10) << myNumber*4.0;
    myPreString = s.str();
    
    // clear stringstream
    s.str("");
    s.clear();
    
    // write to frame buffer object
    fbo.begin();
    ofClear(0, 0, 0, 0);
    drawDigits();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::drawW2(ofEventArgs & args) {
    ofBackground(BGColor, BGColor, BGColor);
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::drawW3(ofEventArgs & args) {
    ofBackground(BGColor, BGColor, BGColor);
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::drawW4(ofEventArgs & args) {
    ofBackground(BGColor, BGColor, BGColor);
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::drawW5(ofEventArgs & args) {
    ofBackground(BGColor, BGColor, BGColor);
    fbo.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::drawW6(ofEventArgs & args) {
    ofBackground(BGColor, BGColor, BGColor);
    fbo.draw(0,0);
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

    // increment phase for each partial and add to output
    for (int i=0; i<bufferSize*nChannels; i+=2) {
        for (int j=0; j<NUM_PARTIALS; ++j) {
            while (phase[j] >= TABLE_SIZE) {
                phase[j] -= TABLE_SIZE;
            }
            while (phase[j] < 0) {
                phase[j] += TABLE_SIZE;
            }
        
            float sample = sinBuf[int(phase[j])]*partialAmp[j]*0.1;
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
        << "\tupdate frequency: " << double(1000.0/timeNow) << " Hz"
        << std::endl;
}

//--------------------------------------------------------------
void ofApp::drawDigits() {
    
    // draw the digits
    int lineIndex = 0;
    int place = 1;
    
    for (int i=0; i<NUM_PARTIALS+1; ++i) {
        float colorScaler;
        myDigit[i] = myPreString.substr(i,1);
        if (myDigit[i] != ".") {
            colorScaler = stof(myDigit[i])*0.1;
        } else {
            colorScaler = 1.0;
        }
        ofSetColor(255*colorScaler, 180*colorScaler, 100*colorScaler);
        myFont.drawString(myDigit[i], place*fontSize*0.8, ofGetHeight()*lineSpacing[lineIndex]);
        ++place;
        if (i == 3 || i == 6) {
            ++lineIndex;
            place = 1;
        }
    }

}
