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

  void readImage();
  void updateBoardClassical(); // classical rules of the game of life
  void updateBoardNew(); // new rule : live if >= 2 living neighbours
  void switchImage();
  void saveImage();
  void printMultipleImages();
  void eraseGliders(int);
  void updateResult_Pxls();
  
  //ofParameterGroup catalyseParameters;
  int threshold;
  int threshold_min;
  int threshold_max;
  int step;
  int channel;
  
  bool if_white;
  bool invert;
  bool eraseBlank;
  bool double_threshold;
  bool limiting_steps;
  bool uniqueInput;
  bool newRule;
  bool first_step_classical;
  bool show_render;
  bool eraseGliders_activated;
  bool preview;

  int livingCell_count, livingCell_minValue;
  
  bool succ;
  int i, j, h, w, count, nombreImages, actualImage, actualStep, living_neighbours;
  int posX, posY, max_value, nombre_zeros;
  int r,g,b;
  int numberNeighbours;
  int* cells;
  bool * rlife_board;
  bool * new_board;
  bool * sum_board;
  ofPixels result_pxls, pxls, startPxls, finalPxls;
  ofFbo result, startFbo, finalFbo;
  ofImage bild;
  ofImage startImage, finalImage;
  
  string input_dir, output_dir, format, file_name, dir_name;
  string input_file, output_file, filePath, main_dir;
  string string_nb_zeros;

};
