#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioOut( float * output, int bufferSize, int nChannels );
    
        double approxPi(double prev_value, int n);
    
        void printToConsole();
    
        const static int TABLE_SIZE = 4096;
        const static int NUM_PARTIALS = 10;
    
        ofTrueTypeFont myFont;
        int fontSize;
        float lineSpacing[3] = {0.3, 0.625, 0.95};
        string myDigit[NUM_PARTIALS+1];
        float myDigitWidth[NUM_PARTIALS+1];
    
        double myNumber = 0;
        int n = 1;
        int sign = -1;
        int iteration = 0;
        double updateDeltaTime = 1000.0/8.75;
        double timeNow;
    
        int sr = 44100;
        float sinBuf[TABLE_SIZE];
        float phase[NUM_PARTIALS];
        float phaseIncrement[NUM_PARTIALS];

        float partialAmp[NUM_PARTIALS];
        float freq = 8.75*9;
    
        stringstream s, s2;
        string myPreString;
};
