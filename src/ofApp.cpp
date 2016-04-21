#include "ofApp.h"
string myPi;

//--------------------------------------------------------------
void ofApp::setup(){

    PiPlayer.open_file(fName);

    // Setting respective transposition factors
    for(int i=0; i<NCHANNELS; i++)
        approximator[i].setTransposeFactor(TRANSPOSITION_FACTOR[i]);
    
    fontSize = WINDOW_HEIGHT*0.25;
    myNumberFont.load("Futura-Medium.ttf", fontSize);
    myPiFont.load("Symbol.ttf", fontSize);
    myStatusFont.load("Futura-Medium.ttf", fontSize*0.25);
    piSymbol.load("pi.png");
    for (int i=0; i<NCHANNELS; ++i)
        fbo[i].allocate(WINDOW_WIDTH, WINDOW_HEIGHT);

    ofSoundStreamSetup(NCHANNELS, 0);
}

//--------------------------------------------------------------
void ofApp::setup_w2(){
    ofBackground(bgColor);
}

//--------------------------------------------------------------
void ofApp::setup_w3(){
    ofBackground(bgColor);
}

//--------------------------------------------------------------
void ofApp::setup_w4(){
    ofBackground(bgColor);
}

//--------------------------------------------------------------
void ofApp::setup_w5(){
    ofBackground(bgColor);
}

//--------------------------------------------------------------
void ofApp::setup_w6(){
    ofBackground(bgColor);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i=0; i<NCHANNELS; ++i)
    {
        // Get latest approximation:
        double latest_approximation = approximator[i].currentApprox;

        ofSetBackgroundColor(bgColor);

        // write to frame buffer object
        fbo[i].begin();
        ofClear(0, 0, 0, 0);
        ofPushMatrix();
        ofTranslate(100, 0);
        if (!status) {
            drawDigits(latest_approximation);
        } else if (status) {
            drawStatus(i+1);
        }
        ofPopMatrix();
        fbo[i].end();
    }
}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for (int i=0; i<bufferSize * nChannels; i+=nChannels) {
        for (int chan=0; chan<nChannels; chan++)
        {
            if(PiPlayer.isPlaying())
                approximator[chan].tick();
            output[i+chan] = PiPlayer.audiofile.next_sample();
        }
        
        // This ensures that you can read the 8-channel file correctly.
        // Increments file pointer so that it reaches the end of the frame.
        for (int chan=0; chan<(PiPlayer.audiofile.getNumChannels()-nChannels); chan++)
        {
            PiPlayer.audiofile.next_sample();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo[0].draw(0,0);
}

//--------------------------------------------------------------
void ofApp::draw_w2(ofEventArgs & args){
    ofBackground(bgColor);
    fbo[1].draw(0,0);
}

//--------------------------------------------------------------
void ofApp::draw_w3(ofEventArgs & args){
    ofBackground(bgColor);
    fbo[2].draw(0,0);
}

//--------------------------------------------------------------
void ofApp::draw_w4(ofEventArgs & args){
    ofBackground(bgColor);
    fbo[3].draw(0,0);
}

//--------------------------------------------------------------
void ofApp::draw_w5(ofEventArgs & args){
    ofBackground(bgColor);
    fbo[4].draw(0,0);
}

//--------------------------------------------------------------
void ofApp::draw_w6(ofEventArgs & args){
    ofBackground(bgColor);
    fbo[5].draw(0,0);
}

//--------------------------------------------------------------
void ofApp::drawDigits(double number){

    piSymbol.draw(100, 20);
    ofSetColor(255, 180, 100);
    ofPushMatrix();
    ofScale(0.7, 1.0);
    myNumberFont.drawString("=", 520, ofGetHeight()*lineSpacing[0]-0);
    ofPopMatrix();
    
    int digits[APPROXIMATOR_PRECISION];
    getDigits(number, digits);    // Get the digits

    int lineIndex = 0;
    int place = 2;
    
    for (int i=0; i<APPROXIMATOR_PRECISION; i++)
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
void ofApp::drawStatus(int wNum){
    int lineSpacing = 50;
    int xMargin = 0;
    
    // draw window number
    ofSetColor(255, 180, 100);
    string wN = "Window: " + to_string(wNum);
    myStatusFont.drawString(wN, xMargin, lineSpacing*1);
    
    // draw time elapsed status
    TimeStruct dur = PiPlayer.getCurrentTime();
    string t_elapsed = "Time elapsed: " + to_string(dur.minutes) + ":" + to_string(dur.seconds);
    myStatusFont.drawString(t_elapsed, xMargin, lineSpacing*2);
    
    // draw play/pause status
    if (PiPlayer.isPlaying()) {
        ofSetColor(0, 255, 0);
        myStatusFont.drawString("Play", xMargin, lineSpacing*3);

    } else {
        ofSetColor(255, 0, 0);
        myStatusFont.drawString("Pause", xMargin, lineSpacing*3);
    }
    
    // draw mute status
    if (PiPlayer.isMuted()) {
        ofSetColor(255, 0, 0);
        myStatusFont.drawString("Mute", xMargin, lineSpacing*4);
    }
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')
        PiPlayer.togglePlay();
    if(key == 'm')
        PiPlayer.toggleMute();
    if(key == 's')
        status = !status;
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