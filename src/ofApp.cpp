#include "ofApp.h"
string myPi;

//--------------------------------------------------------------
void ofApp::setup(){

    audiofile.open_file(fName);
    
    approximator9.setTransposeFactor(TRANSPOSITION_FACTOR[0]);
    
    fontSize = WINDOW_HEIGHT*0.25;
    myNumberFont.load("Futura-Medium.ttf", fontSize);
    myPiFont.load("Symbol.ttf", fontSize);
    piTest.load("pi.png");
    fbo.allocate(WINDOW_WIDTH, WINDOW_HEIGHT);

    ofSoundStreamSetup(2, 0); // 6 output channels (stereo), 0 input channels
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Get latest approximation:
    double latest_approximation = approximator9.currentApprox;

    ofSetBackgroundColor(BGColor+7, BGColor, BGColor);

    // write to frame buffer object
    fbo.begin();
    ofClear(0, 0, 0, 0);
    piTest.draw(100, 20);
    ofSetColor(255, 180, 100);
    ofPushMatrix();
    ofScale(0.7, 1.0);
    myNumberFont.drawString("=", 520, ofGetHeight()*lineSpacing[0]-0);
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(100, 0);
    drawDigits(latest_approximation);
    ofPopMatrix();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for(int i = 0; i < bufferSize * nChannels; i += nChannels) {
        approximator9.tick(); // A sample-accurate approximator tick
        
        float sample = audiofile.next_sample();
//        float sample = 0;
        output[i] = sample;
        output[i+1] = sample;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);

    // TODO: Draw it on multiple screens.
}

//--------------------------------------------------------------
void ofApp::drawDigits(double number){

    int digits[APPROXIMATOR_PRECISION];
    getDigits(number, digits);    // Get the digits

    int lineIndex = 0;
    int place = 2;
    
    for(int i=0; i<APPROXIMATOR_PRECISION; i++)
    {
        float colorScaler;

        // Also draw the dot here
        if(i==1)
        {
            colorScaler = 1.0;
            ofSetColor(255*colorScaler, 180*colorScaler, 100*colorScaler);
            myNumberFont.drawString(".", place*fontSize*0.8, ofGetHeight()*lineSpacing[lineIndex]);
            
        }

        colorScaler = digits[i]*0.1;
        ofSetColor(255*colorScaler, 180*colorScaler, 100*colorScaler);
        myNumberFont.drawString(to_string(digits[i]), place*fontSize*0.8, ofGetHeight()*lineSpacing[lineIndex]);
        ++place;
        if (i == 1 || i == 5)
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