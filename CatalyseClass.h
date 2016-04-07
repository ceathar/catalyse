// CatalyseClass.h

#include "ofMain.h"
#include "lifeRules.h"

class CatalyseClass {
 public:
  int fuckit;

  void setup();
  void draw();
  void update();
  void updateFbo();
  void keyPressed(int key);
  void initStateFromImage(ofPixels, bool, int);
  void initStateFromImageBetweenTwoColors(ofPixels, bool, int, int);

  void readImage();// string filePath="",bool hasParam = false, int zeros=3, string main_dir="input/",string format=".jpg");
  void updateBoardClassical(); // classical rules of the game of life
  void updateBoardNew(); // new rule : live if >= 2 living neighbours
  void eraseGlider(int);

  //ofParameterGroup catalyseParameters;
  ofParameter<int> threshold;
  ofParameter<int> threshold_min;
  ofParameter<int> threshold_max;
  ofParameter<int> step;
  
  bool if_white, eraseBlank, double_threshold, limiting_steps, uniqueInput, newRule;

  int livingCell_count, livingCell_minValue;
  
  bool succ;
  int h, w, count, nombreImages, actualImage, actualStep, living_neighbours;
  int i, max_value, nombre_zeros;
  bool * rlife_board;
  bool * new_board;
  ofPixels result_pxls, pxls;
  ofFbo result;
  ofImage bild;
  
  string input_dir, output_dir, format, file_name, dir_name;
  string input_file, output_file, filePath, main_dir;

};
