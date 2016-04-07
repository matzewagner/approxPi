#pragma once

#include "ofMain.h"
#include "ApproximatePi.h"

#include <iostream>
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

	private:
		ApproximatePi approximator;
		void audioOut( float * output, int bufferSize, int nChannels );
		double phase;
		ofSoundPlayer audioPlayer;

		void drawDigits(float number);
	        ofFbo fbo;		// Needed for drawing

};
