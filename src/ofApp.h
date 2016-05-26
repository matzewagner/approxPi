#pragma once

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024

#include "ofMain.h"
#include "ApproximatePi.h"

#include <iostream>
#include <fstream>
#include <string>
#include "ofxOsc.h"

#define AKSHAY
//#define MATZE

#ifdef AKSHAY
#define SEND_PORT 12345
#define SEND_HOST "matze.local"
#define RECEIVE_PORT 12334
#endif

#ifdef MATZE
#define SEND_PORT 12334
#define SEND_HOST "Akshay.local"
#define RECEIVE_PORT 12345
#endif

using namespace std;

#define NCHANNELS 6
#define SR 44100

class ofApp : public ofBaseApp{
	public:
		void setup();
        void setup_w2();
        void setup_w3();
        void setup_w4();
        void setup_w5();
        void setup_w6();
	
        void update();
    
		void draw();
        void draw_w2(ofEventArgs & args);
        void draw_w3(ofEventArgs & args);
        void draw_w4(ofEventArgs & args);
        void draw_w5(ofEventArgs & args);
        void draw_w6(ofEventArgs & args);
		
		void keyPressed(int key);
		void exit();
		void audioOut( float * output, int bufferSize, int nChannels );
		
        void drawDigits(double number);
        void drawStatus(int wNum);
        void drawBlack();
        void scaleContent(int w, int h);
        void togglePlay();
        void stopPlayback();
        void toggleStatus(int s);
        bool toggleMute();
        bool isPlaying();
    
	private:
		// For doing the approximations
    ApproximatePi approximator[6];

        string fName = ofToDataPath("ApproxPi_8Channel.wav", true);
    
        int counter = 0;
        float *buf;
        int bufReader = 0;
        bool mute = false;
        bool playing = false;
        unsigned long sampleCounter = 0;


        // For Drawing Digits
	    ofFbo fbo[6];
        ofColor bgColor = ofColor(0, 0, 0);
        ofColor fontColor;
        float myHue = 25;
        ofTrueTypeFont myNumberFont, myPiFont, myStatusFont;
        
        int fontSize;
        float verticalFontMargin;
        float lineSpacing[3] = {0.3, 0.625, 0.95};
    
        ofImage piSymbol;

        int status = 2; // 0 = black, 1 = status, 2 = pi
    
        ofxOscSender sender;
        ofxOscReceiver receiver;
    
    
    

};
