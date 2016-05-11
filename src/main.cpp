#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    int wX = 500;
    int wY = 500;
    
    ofGLFWWindowSettings settings;
    settings.width = WINDOW_WIDTH;
    settings.height = WINDOW_HEIGHT;
    settings.setPosition(ofVec2f(wX*0,wY*0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> w1 = ofCreateWindow(settings);
    w1->setWindowTitle("1");
    
    settings.shareContextWith = w1;
    settings.setPosition(ofVec2f(wX*1,wY*0));
    shared_ptr<ofAppBaseWindow> w2 = ofCreateWindow(settings);
    ofSetVerticalSync(false);
    w2->setWindowTitle("2");

    settings.setPosition(ofVec2f(wX*2,wY*0));
    shared_ptr<ofAppBaseWindow> w3 = ofCreateWindow(settings);
    ofSetVerticalSync(false);
    w3->setWindowTitle("3");
    
    settings.setPosition(ofVec2f(wX*0,wY*1));
    shared_ptr<ofAppBaseWindow> w4 = ofCreateWindow(settings);
    ofSetVerticalSync(false);
    w4->setWindowTitle("4");
    
    settings.setPosition(ofVec2f(wX*1,wY*1));
    shared_ptr<ofAppBaseWindow> w5 = ofCreateWindow(settings);
    ofSetVerticalSync(false);
    w5->setWindowTitle("5");
    
    settings.setPosition(ofVec2f(wX*2,wY*1));
    shared_ptr<ofAppBaseWindow> w6 = ofCreateWindow(settings);
    ofSetVerticalSync(false);
    w6->setWindowTitle("6");
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setup_w2();
    mainApp->setup_w3();
    mainApp->setup_w4();
    mainApp->setup_w5();
    mainApp->setup_w6();
    ofAddListener(w2->events().draw, mainApp.get(), &ofApp::draw_w2);
    ofAddListener(w3->events().draw, mainApp.get(), &ofApp::draw_w3);
    ofAddListener(w4->events().draw, mainApp.get(), &ofApp::draw_w4);
    ofAddListener(w5->events().draw, mainApp.get(), &ofApp::draw_w5);
    ofAddListener(w6->events().draw, mainApp.get(), &ofApp::draw_w6);
//
    ofRunApp(w1, mainApp);
	ofRunMainLoop();
}
