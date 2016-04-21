#pragma once

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

#include "ofMain.h"
#include "ApproximatePi.h"

#include <iostream>
#include <fstream>
#include <string>
#include "WavReader.hpp"

using namespace std;

#define NCHANNELS 6


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
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
		void audioOut( float * output, int bufferSize, int nChannels );
		void drawDigits(double number);


	private:
		// For doing the approximations
		ApproximatePi approximator[6];

        string fName = "data/ApproxPi_8ChannelNew.wav";
        WavReader audiofile;
    
        int counter = 0;
        float *buf;
        int bufReader = 0;

        // For Drawing Digits
	    ofFbo fbo[NCHANNELS];
        ofFbo fbo2;
        ofColor bgColor = ofColor(37, 30, 30);
		int BGColor = 30;
        ofTrueTypeFont myNumberFont, myPiFont;
        
        int fontSize;
        float lineSpacing[3] = {0.3, 0.625, 0.95};
    
        ofImage piSymbol;

};
