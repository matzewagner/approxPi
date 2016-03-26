#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void setupW2();
        void setupW3();
        void setupW4();
        void setupW5();
        void setupW6();
		void update();
		void draw();
        void drawW2(ofEventArgs & args);
        void drawW3(ofEventArgs & args);
        void drawW4(ofEventArgs & args);
        void drawW5(ofEventArgs & args);
        void drawW6(ofEventArgs & args);

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
        void drawDigits();
        void printToConsole();
    
        const static int TABLE_SIZE = 4096;
        const static int NUM_PARTIALS = 10;
    
        int BGColor = 30;
        ofTrueTypeFont myFont, windowIndexFont;
        int fontSize;
        float lineSpacing[3] = {0.3, 0.625, 0.95};
        stringstream s;
        string myPreString = "4.0";
        string myDigit[NUM_PARTIALS+1];
        float myDigitWidth[NUM_PARTIALS+1];
    
        double myNumber = 0;
        int n = 1;
        int sign = -1;
        int iteration = 0;
        double updateDeltaTime = 1000/8.75;
        double timeNow;
    
        int sr = 44100;
        float sinBuf[TABLE_SIZE];
        float phase[NUM_PARTIALS];
        float phaseIncrement[NUM_PARTIALS];

        float partialAmp[NUM_PARTIALS];
        float freq = 8.75*9;
    
        ofFbo fbo;
};
