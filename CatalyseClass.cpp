// Catalyse.cpp

#include "CatalyseClass.h"
using namespace ofxCv;
using namespace cv;

void CatalyseClass::setup(){
  posX = 50, posY = 500; // default position for images
  
  // default values
  threshold = 80;
  channel = 0;
  threshold_min = 100;
  threshold_max = 100;
  step = 1;
  preview = true;
  show_render = true;
  
  if_white = false;
  invert = false;
  eraseBlank = false;
  double_threshold = false;
  
  limiting_steps = false;
  uniqueInput = true;
  newRule = false;
  first_step_classical = false;
  eraseGliders_activated = false;
  switchActivated = false;
  setupCanny = false;  
  actualImage = 1;
  actualStep = 0;
  nombreImages = 1440;

  cells = new int[8];
  livingCell_minValue = 1000;

  cannyParam1 = 20;
  cannyParam2 = 6;

  file_name = "Export_version_02_";
  dir_name =  "arbre/";
  file_name = "arbre__";
  main_dir = "input/";
  input_dir = main_dir+dir_name;
  nombre_zeros = 3;
  format = "jpg"; 
  filePath = "test";
  input_file = "input/"+ dir_name + file_name + "0001";

  readImage();
  
  /* still todo: add a function to use a succession of different mode and parameters
     here is a manual version:

  ofDirectory dir;
  dir.allowExt(format);
  dir.open("input/"+dir_name);
  dir.listDir();

  for(int j = 0; j < dir.size()+1; j++) {
    cout << "image : " << j << endl;
    cout << "step 1" << endl;
    filePath = dir_name+"arbre__"+to_string(j);
    readImage();
    
    actualStep = 0;
    step = 50;
    
    invert = false;
    
    for (k = 0; k < step; ++k) {
      updateBoardNew();
    }

    actualStep = step; 
    updateResult_Pxls();
    saveImage();

    cout << "Step 2" << endl;

    for (i = 0; i < count; ++i) {
      rlife_board[i] = !sum_board[i];
    }

    for (i = 0; i < count; ++i) {
      sum_board[i] = !sum_board[i];
    }
    
    step += 50;

    for (k = 0; k < 50; ++k) {
      updateBoardClassical();
    }
    
    for (i = 0; i < count; ++i) {
      if (sum_board[i]) {
    	result_pxls[i * 3] = 0;
    	result_pxls[i * 3 + 1] = 0;
    	result_pxls[i * 3 + 2] = 0;
      }
    }

    actualStep = step;
    saveImage();
    
    cout << "Step 3" << endl;

    for (i = 0; i < count; ++i) {
      rlife_board[i] = !sum_board[i];
    }
    
    step += 50;

    for (k = 0; k < 50; ++k) {
      updateBoardClassical();
    }
    
    for (i = 0; i < count; ++i) {
      if (sum_board[i]) {
    	result_pxls[i * 3] = 0;
    	result_pxls[i * 3 + 1] = 0;
    	result_pxls[i * 3 + 2] = 0;
      }
    }

    actualStep = step;
    saveImage();

    cout << "Step 4" << endl;

    output_canny.getTexture().readToPixels(pxls);
    // get Pxls from canny
    for (i = 0; i < count; ++i) {
      if( (pxls[channel+(i * 3)+1] > threshold) && (result_pxls[i*3]==255)){
  	result_pxls[i * 3] = 80;
  	result_pxls[i * 3 + 1] = 80;
  	result_pxls[i * 3 + 2] = 80;
      }
    }
    
    actualStep = step+100;    
    saveImage();
    }*/
}

void CatalyseClass::updateFbo() {
  result.getTexture().loadData(result_pxls);
}


void CatalyseClass::update() {
  if (actualStep < step) {
    ++actualStep;
    if (newRule) {
      updateBoardNew();
    }
    else {
      updateBoardClassical();
    }
  }
  if(setupCanny) {
    Canny(input_canny,output_canny,cannyParam1*2,cannyParam2*2,3);
    output_canny.update();
  }
}

void CatalyseClass::printMultipleImages() {
  int third_time = 0;
  int tenth_time = 0;
  while (actualImage < nombreImages) {

    string_nb_zeros = "";
    for (i = 0; i < nombre_zeros-log10((actualImage>0) ? actualImage : 1); ++i) {
      string_nb_zeros += "0";
    }
    filePath = dir_name + file_name + string_nb_zeros + to_string(actualImage);
    readImage();
  
    max_value = limiting_steps ? step : actualImage;
    preview = false;
    
    for (k = 0; k < max_value; ++k) {
      if (newRule) {
	updateBoardNew();
      }
      else {
	updateBoardClassical();
      }
    }
    updateResult_Pxls();
    //switchImage();
    saveImage();
    ++actualImage;
  }
  cout << "Done!" << endl; 
}

void CatalyseClass::saveImage() {
  string name = "";
  string tmp_name = (file_name == "") ? filePath : file_name;
  for (i = 0; i < tmp_name.length(); ++i){
    name += tmp_name.at(i);
    if (i == 5) {
      i = tmp_name.length();
    }
  }
  if (uniqueInput) {
    output_file = "output/" +filePath + "-" +to_string(actualStep) + string(".jpg");
  }
  else {
     output_file = "output/" +filePath +to_string(threshold) + "-nbStep" + to_string(actualStep) +"/" + to_string(actualImage) + string(".jpg");
     output_dir = "output/" + dir_name + string(limiting_steps? "L":"noL") + string(eraseBlank? "eB-" : "lB") + string(newRule?"nR":"oR") + "-GTh" + to_string(threshold) + "-iW" + string(if_white?"1":"0") + file_name;
  }
  if (switchActivated) {
    bild.setFromPixels(finalPxls);
  }
  else {
    bild.setFromPixels(result_pxls);
  }
  bild.draw(0, 0);
  bild.save(output_file, OF_IMAGE_QUALITY_BEST);
}

void CatalyseClass::draw() {
  ofBackground(100, 100, 100);
  if (show_render){
    finalFbo.draw(posX,posY,w_draw,h_draw);//,w/2,h/2);
    startFbo.draw(w_draw+posX*2,posY,w_draw/2,h_draw/2);
    result.draw(w_draw+posX*2,posY+h_draw/2,w_draw/2,h_draw/2);
    output_canny.draw(w_draw*1.5+posX*2,posY+h_draw/2,w_draw/2,h_draw/2);
  }
  else {
    result.draw(posX,posY,w_draw,h_draw);//,w/2,h/2);
    startFbo.draw(w_draw+posX*2,posY,w_draw/2,h_draw/2);
    finalFbo.draw(w_draw+posX*2,posY+h_draw/2,w_draw/2,h_draw/2);
    output_canny.draw(w_draw*1.5+posX*2,posY+h_draw/2,w_draw/2,h_draw/2);
  }
}

void CatalyseClass::switchImage() {
  // load new image, twice
  // get rlife_board at final state
  // for each living cell, get Color average of the neighbourhood
  // BASED ON SUM_BOARD

  finalPxls = startPxls;
  for (i = 0; i < count; ++i) {
    numberNeighbours = 0;
    r = 0; g = 0; b = 0; j = 0;
    if (sum_board[i]) {
      cells[0] = i-h-1;
      cells[1] = i-h;
      cells[2] = i-h+1;
      cells[3] = i-1;
      cells[4] = i+1;
      cells[5] = i+h-1;
      cells[6] = i+h;
      cells[7] = i+h+1;
      for (j = 0; j < 8; ++j) {
	if ((cells[j] > 0) && (cells[j] < count) && (!sum_board[cells[j]])){
	  r += startPxls[cells[j]*3];
	  g += startPxls[cells[j]*3 +1];
	  b += startPxls[cells[j]*3 +2];
	  ++numberNeighbours;
	}
      }
      if (numberNeighbours > 0)	{
	finalPxls[i*3] = r / numberNeighbours;
	finalPxls[(i*3)+1] = g / numberNeighbours;
	finalPxls[(i*3)+2] = b / numberNeighbours;
      }
    }
  }
  finalFbo.getTexture().loadData(finalPxls);
}

void CatalyseClass::readImage(){

  if (filePath != "") {
    succ = bild.load(main_dir+filePath+"."+format);
    if (!succ) {
      filePath = ofToLower(filePath);
      succ = bild.load(main_dir+filePath+"."+format);
    }
    succ = input_canny.load(main_dir+filePath+"."+format);
  };
  if (filePath == "" || !succ){
    string_nb_zeros = "";
    for (i = 0; i < nombre_zeros-log10((actualImage>0) ? actualImage : 1); ++i) {
      string_nb_zeros += "0";
    }

    succ = bild.load(input_dir + file_name + string_nb_zeros + to_string(actualImage)+"."+format);
    if (!succ) {
      cerr << "Error when loading image...\n";
      std::exit(1);
    }
    succ = input_canny.load(input_dir + file_name + string_nb_zeros + to_string(actualImage)+"."+format);
  }

  w = bild.getWidth();
  h = bild.getHeight();

  w_draw = w;
  h_draw = h;
  if ((w < ofGetWidth()/3) && (h < ofGetHeight()/3)) {
    w_draw = w * 2;
    h_draw = h * 2;
  }
  // else if (w >= ofGetWidth()) {
  //   w_draw = w / ((ofGetWidth()/w)+2);
  //   h_draw = h / ((ofGetWidth()/w)+2);
  // }
  // else if (h >= ofGetHeight()) {
  //   w_draw = w / ((ofGetHeight()/h)+2);
  //   h_draw = h / ((ofGetHeight()/h)+2);    
  // }

  // bool resize = true;
  // if (resize) {
  //   int new_size = 10;
  //   h = h/new_size;
  //   w = w/new_size;
  // }
  count = h * w;
  bild.resize(w,h);
  startImage = bild;

  // Adding Canny image
  input_canny.setImageType(OF_IMAGE_GRAYSCALE);
  output_canny = input_canny;
  Canny(input_canny,output_canny,cannyParam1*2,cannyParam2*2,3);
  output_canny.update();
  output_canny.setImageType(OF_IMAGE_COLOR);
    
  delete[] rlife_board;
  delete[] sum_board;
  delete[] new_board;

  rlife_board = new bool[count];
  sum_board = new bool[count];
  new_board = new bool[count];

  result.clear();
  result.allocate(w, h, GL_RGB);

  if (setupCanny) {
    output_canny.getTexture().readToPixels(pxls);
  }
  else {
     bild.getTexture().readToPixels(pxls); 
  }
  bild.getTexture().readToPixels(startPxls);

  result.begin();
  ofClear(255, 0, 0);
  result.end();

  result_pxls.clear();
  result.getTexture().readToPixels(result_pxls);

  startFbo.allocate(w, h, GL_RGB);
  startFbo.begin();
  ofClear(255, 0, 0);
  startFbo.end();

  startFbo.getTexture().loadData(pxls);

  finalFbo.allocate(w, h, GL_RGB);
  finalFbo.begin();
  ofClear(255, 0, 0);
  finalFbo.end();

  livingCell_count = 0;
  if (double_threshold) {
    initStateFromImageBetweenTwoColors(pxls, if_white, threshold_min, threshold_max);
  }
  else {
    initStateFromImage(pxls, if_white, threshold);
  }

  finalFbo.getTexture().loadData(pxls);

  // adding a first step with Classical rules
  // to do: adding a timeline:
  if (first_step_classical){
    updateBoardClassical();
  }

  for (i = 0; i < count; ++i) {
    if (rlife_board[i]) {
      livingCell_count++;
      result_pxls[i * 3] = 255 - 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 1] = 255 - 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 2] = 255 - 255 * (invert ? 1 : 0);
    }
    else {
      result_pxls[i * 3] = 0 + 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 1] = 0 + 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 2] = 0 + 255 * (invert ? 1 : 0);
    }
  }
  result.getTexture().loadData(result_pxls);
}

void CatalyseClass::initStateFromImage(ofPixels basePxls, bool val, int threshold) {
  for (i = 0; i < count; ++i) {
    if (basePxls[channel+(i * 3)+1] < threshold){
     rlife_board[i] = val;
     sum_board[i] = val;
    }
    else {
      rlife_board[i] = !val;
      sum_board[i] = !val;
    }
    new_board[i] = false;
  }
}

void CatalyseClass::initStateFromBoard(bool* board, bool val) {
  for (i = 0; i < count; i++) {
    if (board) {
      rlife_board[i] = val;
    }
    else {
      rlife_board[i] = !val;
    }
    new_board[i] = false;
  }
}

void CatalyseClass::initStateFromImageBetweenTwoColors(ofPixels pxls, bool val, int threshold_min, int threshold_max) {
  for (i = 0; i < count; ++i) {
    if ((pxls[channel+(i * 3)] > threshold_min) && (pxls[channel+(i * 3)] < threshold_max)) {
      rlife_board[i] = if_white;
    }
    else rlife_board[i] = val;
    new_board[i] = false;
  }
}

void CatalyseClass::updateBoardClassical() {

  for (i = 0; i < count; ++i) {
    living_neighbours = calcNeighbours(rlife_board, h, w, i);
    if (rlife_board[i]) {
      if (living_neighbours == 2) {
	new_board[i] = true;
	sum_board[i] = true;
      }
      else if (living_neighbours == 3) {
	new_board[i] = true;
	sum_board[i] = true;
      }
      else {
	new_board[i] = false;
      }
    }
    else if (living_neighbours == 3) {
      new_board[i] = true;
      sum_board[i] = true;
    }
    else {
      new_board[i] = false;
    }
  }
  for (i = 0; i < count; ++i) {
    rlife_board[i] = new_board[i];
    if (preview) {
      if (new_board[i]) {	
	result_pxls[i * 3] = 255 - 255 * (invert ? 1 : 0);
	result_pxls[i * 3 + 1] = 255 - 255 * (invert ? 1 : 0);
	result_pxls[i * 3 + 2] = 255 - 255 * (invert ? 1 : 0);
      }
      else if (eraseBlank) {
	result_pxls[i * 3] = 255 - 255 * (invert ? 0 : 1);
	result_pxls[i * 3 + 1] = 255 - 255* (invert ? 0 : 1);
	result_pxls[i * 3 + 2] = 255 - 255 * (invert ? 0 : 1);
      }
    }
    if (eraseGliders_activated){
      for (i = 0; i < count; ++i) {  
	eraseGliders(i);
      }
    }
  }
  updateFbo();
}

void CatalyseClass::updateResult_Pxls() {
  for (i = 0; i < count; ++i) {
    if (sum_board[i]) {	
      result_pxls[i * 3] = 255 - 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 1] = 255 - 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 2] = 255 - 255 * (invert ? 1 : 0);
    }
    else if (eraseBlank) {
      result_pxls[i * 3] = 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 1] = 255 * (invert ? 1 : 0);
      result_pxls[i * 3 + 2] = 255 * (invert ? 1 : 0);
    }
  }
  updateFbo();
}

void CatalyseClass::updateBoardNew() {
  for (i = 0; i < count; ++i) {
    living_neighbours = calcNeighbours(rlife_board, h, w, i);
    if (rlife_board[i]) {
      if (living_neighbours == 2) {
	new_board[i] = true;
	sum_board[i] = true;
      }
      else if (living_neighbours == 3) {
	new_board[i] = true;
	sum_board[i] = true;
      }
      if (living_neighbours >= 4) {
	new_board[i] = true;
	sum_board[i] = true;
      }
      else {
	new_board[i] = false;
      }
    }
    else if (living_neighbours == 3) {
      new_board[i] = true;
      sum_board[i] = true;
    }
    else {
      new_board[i] = false;
    }
  }
  for (i = 0; i < count; ++i) {
    if(preview){
      if (new_board[i]) {
	livingCell_count++;
	result_pxls[i * 3] = 255 - (255 * (invert ? 1 : 0));
	result_pxls[i * 3 + 1] = 255 - (255 * (invert ? 1 : 0));
	result_pxls[i * 3 + 2] = 255 - (255 * (invert ? 1 : 0));
      }
      else if(eraseBlank) {
	result_pxls[i * 3] = 255 * (invert ? 1 : 0);
	result_pxls[i * 3 + 1] = 255 * (invert ? 1 : 0);
	result_pxls[i * 3 + 2] = 255 * (invert ? 1 : 0);
      }
    }
    rlife_board[i] = new_board[i];
  }
  updateFbo();
}

void CatalyseClass::eraseGliders(int c) {
  // Glider Up Right
  if (!rlife_board[c - w - 2] && rlife_board[c - w - 1] && rlife_board[c - w]) {
    if (rlife_board[c - 2] && !rlife_board[c - 1]) {
      if (!rlife_board[c + w - 2] && !rlife_board[c + w - 1] && rlife_board[c + w]) {
	//life_board[i] = false;
	rlife_board[c - 1] = true;
      }
    }
  }
  
  // Glider Up Left
  if (rlife_board[c + 1] && rlife_board[c + 2] && rlife_board[c - h] && rlife_board[c - 2 * h + 1]) {
    if (!rlife_board[c - h + 1] && !rlife_board[c - h + 2] && !rlife_board[c - 2 * h] && !rlife_board[c - 2 * h + 2]) {
      //life_board[i]=false;
      rlife_board[c - 1] = true;
    }
  }
	
  // Glider normal (down-right)
  if (!rlife_board[c - 2 * w - 1] && rlife_board[c - 2 * w] && !rlife_board[c - 2 * w + 1]) {
    if (!rlife_board[c - w - 1] && !rlife_board[c - w] && rlife_board[c - w + 1]) {
      if (rlife_board[c + 1] && rlife_board[c - 1]) {
	//life_board[i] = false;
	rlife_board[c + 2] = true;
      }
    }
  }
	
  // Glider Bottom Left
  if (!rlife_board[c - w + 2] && rlife_board[c - w + 1] && rlife_board[c - w]) {
    if (rlife_board[c + 2] && !rlife_board[c + 1]) {
      if (!rlife_board[c + w + 2] && !rlife_board[c + w + 1] && rlife_board[c + w]) {
	//life_board[i] = false;
	rlife_board[c - 1] = true;
      }
    }
  }
}
