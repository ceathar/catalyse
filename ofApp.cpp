#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  catalyse.setup();

  int x = 50;
  int y = 50;
  autoRefresh = false;
  vector<string> channels = {"RED","GREEN","BLUE"};
  
  f1 = new ofxDatGuiFolder("SETUP");
  f1->addTextInput("FILE","");
  f1->addToggle("WHITE",false);
  //  f1->addToggle("INVERT COLORS",false);
  f1->addToggle("Erase Blank",false);
  f1->addToggle("Limiting Steps",false);
  f1->addToggle("Unique Input",false);
  f1->addToggle("New Rule",false);
  f1->addButton("REFRESH");
  f1->expand();
  f1->onButtonEvent(this,&ofApp::onButtonEvent);
  f1->onTextInputEvent(this,&ofApp::onTextInputEvent);

  f2 = new ofxDatGuiFolder("Threshold");
  f2->addSlider("CHANNELS",0,2);
  f2->addSlider("THRESHOLD",0,255);
  f2->onSliderEvent(this,&ofApp::onSliderEvent);
  //  f2->onDropdownEvent(this,&ofApp::onDropdownEvent);
  f2->addButton("SWITCH");
  f2->onButtonEvent(this,&ofApp::onButtonEvent);
  f2->expand();

  f3 = new ofxDatGuiFolder("ANIMATION");
  f3->addSlider("STEPS",0,2000);
  f3->addToggle("AUTO-REFRESH",false);
  f3->addButton("START");
  f3->onSliderEvent(this,&ofApp::onSliderEvent);
  f3->onButtonEvent(this,&ofApp::onButtonEvent);
  f3->expand();
   
  f1->setPosition(x,y);
  f2->setPosition(x+f1->getWidth()+40,y);
  f3->setPosition(x+f1->getWidth()+40,y+f2->getHeight()+40);

}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e){
  // SETUP
  
  if (e.target->getLabel() == "WHITE") {
     catalyse.if_white = !catalyse.if_white;
  }
  if (e.target->getLabel() == "INVERT COLORS") {
     catalyse.invert = !catalyse.invert;
  }
  if (e.target->getLabel() == "ERASE BLANK") {
     catalyse.eraseBlank = !catalyse.eraseBlank;
  }
  if (e.target->getLabel() == "UNIQUE INPUT") {
     catalyse.uniqueInput = !catalyse.uniqueInput;
  }
  if (e.target->getLabel() == "LIMITING STEPS") {
     catalyse.limiting_steps = !catalyse.limiting_steps;
  }
  if (e.target->getLabel() == "NEW RULE") {
     catalyse.newRule = !catalyse.newRule;
  }
  if (e.target->getLabel() == "REFRESH") {
    catalyse.readImage();
  }
  
  // THRESHOLD
  if (e.target->getLabel() == "SWITCH") {
    catalyse.switchImage();
  }

  // ANIMATION
  if (e.target->getLabel() == "START") {    
  }
  if (e.target->getLabel() == "AUTO-REFRESH") {
    autoRefresh = !autoRefresh;
  }
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e){
  if (e.target->getLabel() == "THRESHOLD") {
    catalyse.threshold = int(e.value);
  }
  if (e.target->getLabel() == "CHANNELS") {
    catalyse.channel = int(e.value);
  }
  if (e.target->getLabel() == "STEPS") {
    catalyse.step = int(e.value);
  }
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e) {
  if (e.target->getLabel() == "FILE") {    
    catalyse.filePath = e.text;
    catalyse.readImage();
  }
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e) {
    cout << "RED" << endl;
    cout << e.child << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
  if (autoRefresh) {
     catalyse.update();
  }

    f1->update();
    f2->update();
    f3->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  catalyse.draw();

  f1->draw();
  f2->draw();
  f3->draw();
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
