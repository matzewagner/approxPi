#include "ofApp.h"
string myPi;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetDataPathRoot("../Resources/data/");
    
    if( !PiPlayer.open_file(fName) )
    {
        cout << "Error opening file" << endl;
        exit();
    }
    
    
    TimeStruct endTime(6, 30);
    PiPlayer.setEndTime(endTime);

    // Setting respective transposition factors
    for(int i=0; i<NCHANNELS; i++)
        approximator[i].setTransposeFactor(TRANSPOSITION_FACTOR[i]);
    
    fontSize = WINDOW_HEIGHT*0.25;
    fontColor = ofColor::fromHsb(50*(255/360), 96, 99);
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
        for (int chan=0; chan<(PiPlayer.audiofile.nChannels()-nChannels); chan++)
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

    int lineIndex = 0;
    int place = 1;
    float letterWidthScaler = 0.8;
    
    piSymbol.draw(0, ofGetHeight()*lineSpacing[0] - piSymbol.getHeight()*1.1);
    
    int digits[APPROXIMATOR_PRECISION];
    getDigits(number, digits);    // Get the digits
    
    // draw the equal sign
    ofPushMatrix();
    fontColor.setHsb(myHue, 255, 255);
    ofSetColor(fontColor);
    ofTranslate((place)*fontSize*0.9, 0);
    ofScale(0.55, 1.0);
    myNumberFont.drawString("=", 0, ofGetHeight()*lineSpacing[0]);
    ofPopMatrix();
    
    // loop over the digits
    ofTranslate(fontSize*0.2, 0);
    for (int i=0; i<APPROXIMATOR_PRECISION; i++)
    {
        float brightnessScaler;
        float saturationScaler;
        
        // offset the letters in the first line by half letter width
        ofPushMatrix();
        if (lineIndex == 0)
            ofTranslate(fontSize*0.4, 0);
        
        // Also draw the dot here
        if(i==1)
        {
            brightnessScaler = 255;
            saturationScaler = 255;
            fontColor.setHsb(myHue, saturationScaler, brightnessScaler);
            ofSetColor(fontColor);
            myNumberFont.drawString(".", (place*fontSize*letterWidthScaler) + (myNumberFont.getLetterSpacing()*fontSize*letterWidthScaler*0.25), ofGetHeight()*lineSpacing[lineIndex]);
            place++;
        }
        
        // draw the digits
        brightnessScaler = (0.3 + digits[i]*0.1)*255;
        saturationScaler = (pow(digits[i]*0.1,2))*255;
        fontColor.setHsb(myHue, 255-saturationScaler, brightnessScaler);
        ofSetColor(fontColor);
        myNumberFont.drawString(to_string(digits[i]), place*fontSize*letterWidthScaler, ofGetHeight()*lineSpacing[lineIndex]);
        ofPopMatrix();
        ++place;
        
        // jump to the beginning of the next line
        if (i == 1 || i == 5)
        {
            ++lineIndex;
            place = 1;
        }
    }
}

//--------------------------------------------------------------
void ofApp::drawStatus(int wNum){
    int lineSpacing = ofGetHeight()*0.2;
    int xMargin = 100;
    
    // draw window number
    fontColor.setHsb(myHue, 255, 255);
    ofSetColor(fontColor);
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
    if(key == '0')
    {
        PiPlayer.stop();
        for(int i=0; i<NCHANNELS; i++)
            approximator[i].Reset();
    }
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