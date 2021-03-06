// CatalyseClass.h

#include "ofMain.h"
#include "lifeRules.h"
#include "ofxCv.h"

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
  void initStateFromBoard(bool*,bool);
  void readImage();
  void updateBoardClassical(); // classical rules of the game of life
  void updateBoardNew(); // new rule : live if >= 2 living neighbours
  void switchImage();
  void saveImage();
  void printMultipleImages();
  void eraseGliders(int);
  void updateResult_Pxls();
  
  //Parameters
  int threshold;
  int threshold_min;
  int threshold_max;
  int step;
  int channel;
  // Canny Parameters
  int cannyParam1, cannyParam2;
  
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
  bool setupCanny;
  bool switchActivated;

  int livingCell_count, livingCell_minValue;
  
  bool succ;
  int i, j, k, nombreImages, actualImage, actualStep, living_neighbours;
  int h,w,count,h_draw, w_draw, posX, posY;
  int max_value, nombre_zeros;
  int r,g,b;
  int numberNeighbours;
  
  int* cells;
  bool * rlife_board;
  bool * new_board;
  bool * sum_board;
  
  ofPixels result_pxls, pxls, startPxls, finalPxls;
  ofFbo result, startFbo, finalFbo;
  ofImage bild;
  ofImage input_canny,output_canny, fuck_me;
  ofImage startImage, finalImage;
  
  string input_dir, output_dir, format, file_name, dir_name;
  string input_file, output_file, filePath, main_dir;
  string string_nb_zeros;

};
