#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  catalyse.setup();
  parameterGroup.add(catalyse.catalyseParameters);
  gui.setup(parameterGroup);
}

//--------------------------------------------------------------
void ofApp::update(){
    catalyse.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  catalyse.draw();
  gui.draw();
}

void ofApp::paramChanged(){
  catalyse.readImage();
  catalyse.actualStep = 0;
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
  catalyse.readImage();
  catalyse.actualStep = 0;
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
