#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    const double ONEOVERSHORTMAX = 1.0/32768;
    
    char ChunkID[4], Format[4], Subchunk1ID[4],Subchunk2ID[4];
    int ChunkSize,Subchunk1Size, SampleRate, ByteRate,Subchunk2Size;
    short AudioFormat, NumChannels, BlockAlign, BitsPerSample;
    
    short *Data;
    // Read the wave file
    FILE *fhandle=fopen(fName,"rb");
    fread(ChunkID,1,4,fhandle);
    fread(&ChunkSize,4,1,fhandle);
    fread(Format,1,4,fhandle);
    fread(Subchunk1ID,1,4,fhandle);
    fread(&Subchunk1Size,4,1,fhandle);
    fread(&AudioFormat,2,1,fhandle);
    fread(&NumChannels,2,1,fhandle);
    fread(&SampleRate,4,1,fhandle);
    fread(&ByteRate,4,1,fhandle);
    fread(&BlockAlign,2,1,fhandle);
    fread(&BitsPerSample,2,1,fhandle);
    fread(&Subchunk2ID,1,4,fhandle);
    fread(&Subchunk2Size,4,1,fhandle);
    int nSamples = Subchunk2Size/(BitsPerSample/8);
    Data = new short[nSamples];
    buf = new float[nSamples];
    fread(Data, BitsPerSample/8, nSamples, fhandle);
    
    fclose(fhandle);
    
    for (int i=0; i<nSamples; ++i)
        buf[i] = Data[i] * ONEOVERSHORTMAX;
    
    fontSize = WINDOW_HEIGHT*0.25;
    myFont.load("Futura-Medium.ttf", fontSize);
    fbo.allocate(WINDOW_WIDTH, WINDOW_HEIGHT);

    ofSoundStreamSetup(2, 0); // 6 output channels (stereo), 0 input channels
//    ofSoundStreamStart();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // Get latest approximation:
    double latest_approximation = approximator.currentApproxTransposed;

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
        approximator.tick(); // A sample-accurate approximator tick
        
        float sample = buf[bufReader];
//        float sample = 0;
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