#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

    int wWidth = 450;
    int wHeight = 450;
    
    ofGLFWWindowSettings settings;
    settings.width = wWidth;
    settings.height = wHeight;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setWindowTitle("main");
    
    settings.setPosition(ofVec2f(wWidth*1, 0));
    settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> window2 = ofCreateWindow(settings);
    window2->setWindowTitle("2");
    
    settings.setPosition(ofVec2f(wWidth*2, 0));
    shared_ptr<ofAppBaseWindow> window3 = ofCreateWindow(settings);
    window3->setWindowTitle("3");
    
    settings.setPosition(ofVec2f(0,wHeight*1));
    shared_ptr<ofAppBaseWindow> window4 = ofCreateWindow(settings);
    window4->setWindowTitle("4");
    
    settings.setPosition(ofVec2f(wWidth*1, wHeight*1));
    shared_ptr<ofAppBaseWindow> window5 = ofCreateWindow(settings);
    window5->setWindowTitle("5");
    
    settings.setPosition(ofVec2f(wWidth*2,wHeight*1));
    shared_ptr<ofAppBaseWindow> window6 = ofCreateWindow(settings);
    window6->setWindowTitle("6");

    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupW2();
    mainApp->setupW3();
    mainApp->setupW4();
    mainApp->setupW5();
    mainApp->setupW6();
    
    ofAddListener(window2->events().draw,mainApp.get(),&ofApp::drawW2);
    ofAddListener(window3->events().draw,mainApp.get(),&ofApp::drawW3);
    ofAddListener(window4->events().draw,mainApp.get(),&ofApp::drawW4);
    ofAddListener(window5->events().draw,mainApp.get(),&ofApp::drawW5);
    ofAddListener(window6->events().draw,mainApp.get(),&ofApp::drawW6);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
}
