#include "ofApp.h"
#include <String>
#include <sstream>
#include <iomanip>

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30, 30, 30);
    fontSize = int(ofGetHeight()*0.25);
    myFont.load("Futura-Medium.ttf", fontSize);

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // approximate pi
    myNumber = approxPi(myNumber, n);
    
    // convert nyNumber into 3 substrings
    s << std::fixed << std::setprecision(10) << myNumber*4.0;
    myPreString = s.str();
    myString1 = myPreString.substr(0, 4);
    myString2 = myPreString.substr(4, 3);
    myString3 = myPreString.substr(7, 4);
    
    // get width of strings
    sWidth1 = myFont.getStringBoundingBox(myString1, ofGetWidth()*0.5, ofGetHeight()*0.3).getWidth();
    sWidth2 = myFont.getStringBoundingBox(myString2, ofGetWidth()*0.5, ofGetHeight()*0.625).getWidth();
    sWidth3 = myFont.getStringBoundingBox(myString3, ofGetWidth()*0.5, ofGetHeight()*0.95).getWidth();
    
    // draw strings
    ofSetColor(200, 180, 100);
    myFont.drawString(myString1, ofGetWidth()*0.5 - sWidth1*0.5, ofGetHeight()*0.3);
    myFont.drawString(myString2, ofGetWidth()*0.5 - sWidth2*0.5, ofGetHeight()*0.625);
    myFont.drawString(myString3, ofGetWidth()*0.5 - sWidth3*0.5, ofGetHeight()*0.95);
    
    // clear stringstream
    s.str("");
    s.clear();
    
    // increment term
    n+=2;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    drawLine = !drawLine;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
double ofApp::approxPi(double prev_value, int n) {
    
    
    sign *= -1;
    return prev_value + sign/double(n);
    
}
