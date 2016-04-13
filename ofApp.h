#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "CatalyseClass.h"


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

		void onSliderEvent(ofxDatGuiSliderEvent e);
		void onDropdownEvent(ofxDatGuiDropdownEvent e);
		void onTextInputEvent(ofxDatGuiTextInputEvent e);
		void onSwitchEvent(ofxDatGuiButtonEvent e);
		void onButtonEvent(ofxDatGuiButtonEvent e);
  
		ofxDatGuiFolder* f1;
		ofxDatGuiFolder* f2;
		ofxDatGuiFolder* f3;
		ofxDatGuiFolder* f4;

		bool autoRefresh;
		CatalyseClass catalyse;
};
