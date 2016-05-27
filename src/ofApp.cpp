#include "ofApp.h"
string myPi;

//--------------------------------------------------------------
void ofApp::setup(){
    
//    ofSetDataPathRoot("../Resources/data/");
    
    receiver.setup(RECEIVE_PORT);
    sender.setup(SEND_HOST, SEND_PORT);

    // Setting respective transposition factors
    for(int i=0; i<NCHANNELS; i++)
        approximator[i].setTransposeFactor(TRANSPOSITION_FACTOR[i]);
    
    fontSize = min(WINDOW_WIDTH, WINDOW_HEIGHT)*0.25;
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
void ofApp::togglePlay() {
    playing = !playing;
}

//--------------------------------------------------------------
void ofApp::stopPlayback() {
    
    for(int i=0; i<NCHANNELS; i++) {
        approximator[i].Reset();
    }
<<<<<<< HEAD

=======
    playing = false;
    sampleCounter = 0;
>>>>>>> 7a4dc265ee69fb15d54cc0a868bd32385b4948cf
}

//--------------------------------------------------------------
void ofApp::toggleStatus(int s) {
    status = s;
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
        ofTranslate(fontSize*0.6,  verticalFontMargin);
        ofClear(0, 0, 0, 0);
        ofPushMatrix();
        if (status == 2) {
            drawDigits(latest_approximation);
        } else if (status == 1) {
            drawStatus(i+1);
        } else if (status == 0) {
            drawBlack();
        }
        ofPopMatrix();
        fbo[i].end();
    }
    
    // check for waiting messages
    while( receiver.hasWaitingMessages() )
    {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        if (m.getAddress() == "/togglePlay")
        {
            togglePlay();
        }
        if (m.getAddress() == "/reset")
        {
            stopPlayback();
        }
        if (m.getAddress() == "/toggleMute")
        {
            toggleMute();
        }
        if (m.getAddress() == "/toggleStatus")
        {
            int statusValue = m.getArgAsInt(0);
            toggleStatus(statusValue);
        }
    }

}

//--------------------------------------------------------------
void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    for (int i=0; i<bufferSize * nChannels; i+=nChannels) {
        for (int chan=0; chan<nChannels; chan++)
        {
            // check for when the piece should end
            if (sampleCounter >= END_TIME_IN_MINUTES*60.0*SR && sampleCounter%4410 == 0)
            {
                if (!approximator[chan].hasEnded() && endFlag)
                {
                    approximator[chan].end();
                    endFlag = false;
                }
            }
            
            if (isPlaying() && !approximator[chan].hasEnded())
            {
                if(mute)
                {
                    approximator[chan].tick();
                    output[i+chan] = 0;
                }
                else
                {
                    output[i+chan] = approximator[chan].tick();
                }
                
            }
        }
<<<<<<< HEAD
    
=======
        
        
        if (isPlaying())
        {
            ++sampleCounter;
        }
        
        if (sampleCounter >= END_TIME_IN_MINUTES*60.0*SR)
        {
            endFlag = true;
        }
>>>>>>> 7a4dc265ee69fb15d54cc0a868bd32385b4948cf
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    if (!approximator[0].hasEnded())
    {
        scaleContent(ofGetWindowWidth(), ofGetWindowHeight());
        fbo[0].draw(0,0);
    }
    else
    {
        drawBlack();
    }

}

////--------------------------------------------------------------
void ofApp::draw_w2(ofEventArgs & args){
    if (!approximator[1].hasEnded())
    {
        scaleContent(ofGetWindowWidth(), ofGetWindowHeight());
        ofBackground(bgColor);
        fbo[1].draw(0,0);
    }
    else
    {
        drawBlack();
    }
}

//--------------------------------------------------------------
void ofApp::draw_w3(ofEventArgs & args){
    if (!approximator[2].hasEnded())
    {
        scaleContent(ofGetWindowWidth(), ofGetWindowHeight());
        ofBackground(bgColor);
        fbo[2].draw(0,0);
    }
    else
    {
        drawBlack();
    }
}

//--------------------------------------------------------------
void ofApp::draw_w4(ofEventArgs & args){
    if (!approximator[3].hasEnded())
    {
        scaleContent(ofGetWindowWidth(), ofGetWindowHeight());
        ofBackground(bgColor);
        fbo[3].draw(0,0);
    }
    else
    {
        drawBlack();
    }
}

//--------------------------------------------------------------
void ofApp::draw_w5(ofEventArgs & args){
    if (!approximator[4].hasEnded())
    {
        scaleContent(ofGetWindowWidth(), ofGetWindowHeight());
        ofBackground(bgColor);
        fbo[4].draw(0,0);
    }
    else
    {
        drawBlack();
    }
}

//--------------------------------------------------------------
void ofApp::draw_w6(ofEventArgs & args){
    if (!approximator[5].hasEnded())
    {
        scaleContent(ofGetWindowWidth(), ofGetWindowHeight());
        ofBackground(bgColor);
        fbo[5].draw(0,0);
    }
    else
    {
        drawBlack();
    }
}

//--------------------------------------------------------------
void ofApp::drawBlack()
{
    return;
}

//--------------------------------------------------------------
bool ofApp::isPlaying()
{
    return playing;
}

//--------------------------------------------------------------
void ofApp::drawDigits(double number){

    int lineIndex = 1;
    int place = 1;
    float letterWidthScaler = 0.8;
    verticalFontMargin = fontSize*0.15;

    
    piSymbol.draw(-fontSize*0.5, verticalFontMargin);
    
    int digits[APPROXIMATOR_PRECISION];
    getDigits(number, digits);    // Get the digits
    
    // draw the equal sign
    ofPushMatrix();
    fontColor.setHsb(myHue, 255, 255);
    ofSetColor(fontColor);
    ofTranslate(0.75*fontSize, 0);
    ofScale(0.55, 1.0);
    myNumberFont.drawString("=", 0, (fontSize + verticalFontMargin) * lineIndex);
    ofPopMatrix();
    
    // loop over the digits
    for (int i=0; i<APPROXIMATOR_PRECISION; i++)
    {
        float brightnessScaler;
        float saturationScaler;
        
        // offset the letters in the first line by half letter width
        ofPushMatrix();
        if (lineIndex == 1)
            ofTranslate(fontSize*0.4, 0);
        
        // Also draw the dot here
        if (i==1)
        {
            brightnessScaler = 255;
            saturationScaler = 255;
            fontColor.setHsb(myHue, saturationScaler, brightnessScaler);
            ofSetColor(fontColor);
            myNumberFont.drawString(".", (place*fontSize*letterWidthScaler) + (myNumberFont.getLetterSpacing()*fontSize*letterWidthScaler*0.25), (fontSize + verticalFontMargin) * lineIndex);
            place++;
        }
        
        // draw the digits
        brightnessScaler = (0.3 + digits[i]*0.1)*255;
        saturationScaler = (pow(digits[i]*0.1,2))*255;
        fontColor.setHsb(myHue, 255-saturationScaler, brightnessScaler);
        ofSetColor(fontColor);
        myNumberFont.drawString(to_string(digits[i]), place*fontSize*letterWidthScaler, (fontSize + verticalFontMargin) * lineIndex);
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
    int lineSpacing = (fontSize+verticalFontMargin)*0.75;
    int xMargin = 100;
    
    // draw window number
    fontColor.setHsb(myHue, 255, 255);
    ofSetColor(fontColor);
    string wN = "Window: " + to_string(wNum);
    myStatusFont.drawString(wN, xMargin, lineSpacing*1);
    
    // draw time elapsed status
    float seconds = sampleCounter / float(SR);
    int displayHours = std::floor(seconds/3600.0);
    int displayMinutes = std::floor(std::fmod((seconds/60.0),60.0));
    int displaySeconds = std::fmod(seconds,60);
    
    std::string time = ofToString(displayHours) + ":" + ofToString(displayMinutes) + ":" + ofToString(displaySeconds);
    myStatusFont.drawString(time, xMargin, lineSpacing*2);
    
    // draw play/pause status
    if (isPlaying()) {
        ofSetColor(0, 255, 0);
        myStatusFont.drawString("Play", xMargin, lineSpacing*3);

    } else {
        ofSetColor(255, 0, 0);
        myStatusFont.drawString("Pause", xMargin, lineSpacing*3);
    }
    
    // draw mute status
    if (mute) {
        ofSetColor(255, 0, 0);
        myStatusFont.drawString("Mute", xMargin, lineSpacing*4);
    }
}

//--------------------------------------------------------------
void ofApp::scaleContent(int w, int h) {
    float horizontalWindowScaleFactor = w / float(fontSize*6.0);
    float verticalWindowScaleFactor = h / float(fontSize*3.8);
    ofScale(horizontalWindowScaleFactor, verticalWindowScaleFactor);
}
//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ')
    {
        ofxOscMessage m;
        m.setAddress("/togglePlay");
        sender.sendMessage( m );
        
        togglePlay();
        
    }
    if(key == 'm')
    {
        ofxOscMessage m;
        m.setAddress("/toggleMute");
        sender.sendMessage( m );
        
        toggleMute();
    }
    if(key == '1')
    {
        status = 0;
        ofxOscMessage m;
        m.setAddress("/toggleStatus");
        m.addIntArg(status);
        sender.sendMessage( m );
        
    }
    if(key == '2')
    {
        status = 1;
        ofxOscMessage m;
        m.setAddress("/toggleStatus");
        m.addIntArg(status);
        sender.sendMessage( m );

    }
    if(key == '3')
    {
        status = 2;
        ofxOscMessage m;
        m.setAddress("/toggleStatus");
        m.addIntArg(status);
        sender.sendMessage( m );

    }
    if(key == '0')
    {
        ofxOscMessage m;
        m.setAddress("/reset");
        sender.sendMessage( m );
        
        stopPlayback();
    }

}

//--------------------------------------------------------------

bool ofApp::toggleMute()
{
    mute = !mute;
    return mute;
}