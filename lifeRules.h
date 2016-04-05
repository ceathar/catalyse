/* lifeRules.h
*  Created by leyokki on 10/01/16.
*  Here are defintions which outputs something different than void
*
*/

#ifndef __LIFERULES_H__
#define __LIFERULES_H__

#include "ofMain.h"

class ofLifeRules {

public:


};

// calc number of living neighbours around a cell
int calcNeighbours(bool*, int, int, int);
ofColor getColorAverage(ofImage, int, int);

// updating Pictures
ofImage updatePictureBW(bool*, ofImage, int);
ofImage updatePictureAddColor(bool*, ofImage, ofColor);
ofImage updatePictureColor(bool*, bool*, ofImage, ofImage);
ofImage updatePictureTrichrome(bool*, bool*, bool*, bool*, ofImage);
void saveImage(ofImage, int, string);

// printREL
string printREL(bool*, int, int);

#endif
