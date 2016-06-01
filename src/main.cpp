#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    int init_windowWidth = 450;
    int init_windowHeight = 400;
    
    int wX = init_windowWidth;
    int wY = init_windowHeight + 75;
    
    ofGLFWWindowSettings settings;
    settings.width = 1400;
    settings.height = 900;
    settings.setPosition(ofVec2f(wX*0,wY*0));
    settings.resizable = true;
    settings.multiMonitorFullScreen = true;
    shared_ptr<ofAppBaseWindow> w1 = ofCreateWindow(settings);
    w1->setWindowTitle("approximating Pi");
    
    shared_ptr<ofApp> mainApp(new ofApp);
    
    ofRunApp(w1, mainApp);
	ofRunMainLoop();
}
