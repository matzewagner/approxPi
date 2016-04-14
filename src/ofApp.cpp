#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

    sf = sf_open(fName, SFM_READ, &info);
    if (sf==NULL)
        printf("Failed to open audio file.\n");
    
    int nSamples = info.frames * info.channels;
    buf = (float*)malloc(nSamples*sizeof(float));
    
    sf_read_float(sf, buf, nSamples);
    
    fontSize = WINDOW_HEIGHT*0.25;
    myFont.load("Futura-Medium.ttf", fontSize);
    fbo.allocate(WINDOW_WIDTH, WINDOW_HEIGHT);

    ofSoundStreamSetup(2, 0); // 6 output channels (stereo), 0 input channels
//    ofSoundStreamStart();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Get latest approximation:
    double latest_approximation = approximator.currentApprox;

    ofSetBackgroundColor(BGColor+7, BGColor, BGColor);

    // write to frame buffer object
    fbo.begin();
    ofClear(0, 0, 0, 0);
    drawDigits(latest_approximation);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for(int i = 0; i < bufferSize * nChannels; i += nChannels) {
        if (bufReader%560 == 0)
            approximator.tick(); // A sample-accurate approximator tick
        
        float sample = buf[bufReader];
        output[i] = sample;
        output[i+1] = sample;
        ++bufReader;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);

    // TODO: Draw it on multiple screens.
}

//--------------------------------------------------------------
void ofApp::drawDigits(double number){

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

        colorScaler = digits[i]*0.1;
        ofSetColor(255*colorScaler, 180*colorScaler, 100*colorScaler);
        myFont.drawString(to_string(digits[i]), place*fontSize*0.8, ofGetHeight()*lineSpacing[lineIndex]);
        ++place;
        if (i == 2 || i == 6)
        {
            ++lineIndex;
            place = 1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
    sf_close(sf);
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