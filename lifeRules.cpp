// lifeRules.cpp

#include "lifeRules.h"

int calcNeighbours(bool *life_board, int h, int w, int c) {
	// Calculate the numbers of living cells in the neighbourhood of a cell.
	int living_neighbours = 0;
	if (c - 1 >= 0) {
		if (life_board[c - 1]) {
			living_neighbours++;
		}
	}
	if (c + 1 <= w*h) {
		if (life_board[c + 1]) {
			living_neighbours++;
		}
	}
	if (c - w >= 0) {
		if (life_board[c - w]) {
			living_neighbours++;
		}
	}
	if (c - (w - 1) >= 0) {
		if (life_board[c - (w - 1)]) {
			living_neighbours++;
		}
	}
	if (c - (w + 1) >= 0) {
		if (life_board[c - (w + 1)]) {
			living_neighbours++;
		}
	}
	if (c + w <= w*h) {
		if (life_board[c + w]) {
			living_neighbours++;
		}
	}
	if (c + (w - 1) <= w*h) {
		if (life_board[c + (w - 1)]) {
			living_neighbours++;
		}
	}
	if (c + (w + 1) <= w*h) {
		if (life_board[c + (w + 1)]) {
			living_neighbours++;
		}
	}
	return living_neighbours;
}

ofColor getColorAverage(ofImage image, int i, int j) {
	int RAverage = 0; int BAverage = 0; int GAverage = 0; // average for R, G, B
	int count = 1;
	int h = image.getHeight();
	int w = image.getWidth();
	ofColor pixel = image.getColor(i, j);
	if (i >= 1) {
		if (j >= 1) {
			pixel = image.getColor(i - 1, j - 1);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
		if (j >= 0) {
			pixel = image.getColor(i - 1, j);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
		if (j + 1 <= h) {
			pixel = image.getColor(i - 1, j + 1);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
	}

	if (i >= 0) {
		if (j - 1 >= 0) {
			ofColor pixel = image.getColor(i, j - 1);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
		if (j >= 0) {
			ofColor pixel = image.getColor(i, j);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
		if (j + 1 <= w) {
			ofColor pixel = image.getColor(i, j + 1);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
	}

	if (i + 1 <= h) {
		if (j - 1 >= 0) {
			ofColor pixel = image.getColor(i + 1, j - 1);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
		if (j >= 0) {
			ofColor pixel = image.getColor(i + 1, j);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
		if (j + 1 <= w) {
			ofColor pixel = image.getColor(i + 1, j + 1);
			RAverage += pixel.r;
			GAverage += pixel.g;
			BAverage += pixel.b;
			count++;
		}
	}
	return ofColor(RAverage%count, GAverage%count, BAverage%count);
}

ofImage updatePictureBW(bool *next_state, ofImage image, int color) {
	// Updating picture B&W
	int c = 0;
	int h = image.getHeight();
	int w = image.getWidth();
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (next_state[c]) {
				//printf("1");
				image.setColor(i, j, ofColor(255 * color, 255 * color, 255 * color));
			}
			else {
				//printf("0\n");
				image.setColor(i, j, ofColor(255 - (color * 255), 255 - (color * 255), 255 - (color * 255)));
			}
			c++;
		}
		//printf("\n");
	}
	//printf("\n");
	image.update();
	return image;
}

ofImage updatePictureAddColor(bool *next_state, ofImage image, ofColor color) {
	// Updating picture with black color
	// Add only if cell is alive
	int c = 0;
	int h = image.getHeight();
	int w = image.getWidth();
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			if (next_state[c]) {
				image.setColor(i, j, color);
			}
			else {
				//image.setColor(i,j,ofColor(255,255,255));
			}
			c++;
		}
	}
	image.update();
	return image;
}


ofImage updatePictureColor(bool *next_state, bool *old_state, ofImage image, ofImage copymage) {
	// Updating picture with color
	int c = 0;
	int h = image.getHeight();
	int w = image.getWidth();
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			// Check next state
			if (next_state[c]) {
				// if it is an old state (already alive)
				if (old_state[c]) {
					image.setColor(i, j, image.getColor(i, j));
				}
				// if a new cell
				else {
					ofColor newColor = getColorAverage(image, i, j);
					image.setColor(i, j, newColor);
				}
			}
			else {
				// if cell is dead : white
				image.setColor(i, j, ofColor(255, 255, 255));
			}
			c++;
		}
	}
	return image;
}

// STILL WIP : SUCCEED BUT ISN'T REALLY INTERESTING
ofImage updatePictureTrichrome(bool *redstate, bool* greenstate, bool *bluestate, bool *old_state, ofImage image) {
	// Updating picture with color
	int c = 0;
	int rangeColor[6] = { 13269050,6432541,10647630,11835781,5191971,7549988 };
	int h = image.getHeight();
	int w = image.getWidth();
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {

			ofColor pixel = image.getColor(i, j);

			if (redstate[c]) {
				if (pixel.r == 255 && pixel.g == 255 && pixel.b == 255) {
					int newRandomNumber = rand() % 4;
					int randomNumber = (int)(newRandomNumber + 1);
					pixel.setHex(rangeColor[randomNumber]);
				}
			}
			image.setColor(i, j, pixel);//ofColor(r,g,b));
		}
	}
	return image;
}

void saveImage(ofImage image, int numEntree, string description) {
	string numString;
	ostringstream convert;
	convert << numEntree;
	numString = convert.str();
	image.saveImage("exports/" + description + numString + ".png", OF_IMAGE_QUALITY_BEST);
}


string printREL(bool *etats, int c, int size_line) {
	// b = dead cell;
	// o = live cell;
	// $ = EOF;
	string text = "";
	bool val = etats[0];
	int count = 1;
	int no_line = 0;
	
	
	for (int i = 0; i < c; i++){
		string state = val ? "o" : "b";
		
		if (no_line >= size_line) {
			if (count == 1) {
				text += state+"$";
			} else {
				text += to_string(count)+state+"$";
			}
			no_line = 0;
			count = 1;
		}
		
		else if (etats[i] == val) {
			count++;
		} else {
			if (count == 1) {
				text += state;
			} else {
				text += to_string(count)+state;
			}
			val = !val;
			count = 1;
		}
		no_line++;		
		val = etats[i];
	}
	return text;
}

