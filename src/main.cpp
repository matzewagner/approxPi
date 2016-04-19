#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

//	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
    
    ofGLFWWindowSettings settings;
    settings.width = WINDOW_WIDTH;
    settings.height = WINDOW_HEIGHT;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setWindowTitle("main");
    
    shared_ptr<ofApp> mainApp(new ofApp);
    
    ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
