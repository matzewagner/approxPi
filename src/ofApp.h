#pragma once

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#include "ofMain.h"
#include "ApproximatePi.h"

#include <iostream>
#include <string>
using namespace std;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
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
		ApproximatePi approximator;

		// TODO: Include a soundfile object 

        // For Drawing Digits
	    ofFbo fbo;
		int BGColor = 30;
        ofTrueTypeFont myFont;
        int fontSize;
        float lineSpacing[3] = {0.3, 0.625, 0.95};
};
