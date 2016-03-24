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
    
        ofTrueTypeFont myFont;
        int fontSize;
    
        double myNumber = 0.0;
        int n = 1;
        int sign = -1;
        int iteration = 0;
        float updateFrequency = 1000.0/8.75;
        float timeNow;
    
        std::stringstream s;
        std::string myPreString, myString1, myString2, myString3;
    
        float sWidth1, sWidth2, sWidth3;
		
};
