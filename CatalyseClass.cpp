

// Catalyse.cpp

#include "CatalyseClass.h"

void CatalyseClass::setup(){
  posX = 50, posY = 500;
  
  // default values
  threshold = 100;
  channel = 1;
  threshold_min = 100;
  threshold_max = 100;
  step = 1;
  preview = true;

  if_white = false;
  invert = false;
  eraseBlank = false;
  double_threshold = false;
  limiting_steps = false;
  uniqueInput = false;
  newRule = false;
  first_step_classical = false;
  eraseGliders_activated = false;
  
  actualImage = 2324;
  actualStep = 0;
  nombreImages = 3324;
  show_render = true;

  cells = new int[8];
  livingCell_minValue = 1000;

  dir_name =  "film/";
  file_name = "Export_version_02_";
  input_dir = "input/"+dir_name;
  nombre_zeros = 3;
  format = ".jpg";

  main_dir = "input/";
  filePath = "";

  input_file = "input/"+ dir_name + file_name + "0001";
  output_dir = "output/" + dir_name + string(limiting_steps? "L":"noL") + string(eraseBlank? "eB-" : "lB") + string(newRule?"nR":"oR") + "-GTh" + to_string(threshold) + "-iW" + string(if_white?"1":"0") + "/" + file_name;
  
  readImage();
}

void CatalyseClass::updateFbo() {
  result.getTexture().loadData(result_pxls);
}

void CatalyseClass::update() {
  //for (i = 0; i < step; ++i) {
  if (actualStep < step) {
    ++actualStep;
    if (newRule) {
      updateBoardNew();
    }
    else {
      updateBoardClassical();
    }
    bild.setFromPixels(result_pxls);
  }
  /*else {
    readImage();
    actualStep = 0;
    }*/
}

void CatalyseClass::printMultipleImages() {
  while (actualImage < nombreImages) {
    //    int no_image = actualImage;

    string_nb_zeros = "";
    for (i = 0; i < nombre_zeros-log10((actualImage>0) ? actualImage : 1); ++i) {
      string_nb_zeros += "0";
    }
    filePath = dir_name + file_name + string_nb_zeros + to_string(actualImage);
    readImage();
  
    max_value = limiting_steps ? step : actualImage;
    preview = false;
    
    for (actualStep = 0; i < max_value; ++i) {
      if (newRule) {
	updateBoardNew();
      }
      else {
	updateBoardClassical();
      }
    }
    updateResult_Pxls();
    switchImage();
    saveImage();
    ++actualImage;
  }
  cout << "Done!" << endl; 
  //std::exit(0);
      // if (uniqueInput) {
      // 	cout << i << " - ";
      // 	output_file = output_dir + to_string(no_image) + "/" + to_string(actualImage) + string(".jpg");
      // 	bild.setFromPixels(result_pxls);
      // 	++actualImage;
      // 	bild.save(output_file, OF_IMAGE_QUALITY_BEST);
      // }
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
  //output_dir = "output/" + name + string(limiting_steps? "L":"noL") + string(eraseBlank? "eB-" : "lB") + string(newRule?"nR":"oR") + "-GTh" + to_string(threshold) + "-iW" + string(if_white?"1":"0") + "/"+ to_string(actualImage);
  //  output_file = output_dir + file_name + string(".jpg");
  output_file = "output/film-GTh" +to_string(threshold) + "-nbStep" + to_string(actualStep) +"/" + to_string(actualImage) + string(".jpg");
  bild.setFromPixels(finalPxls);//result_pxls);
  bild.draw(0, 0);
  bild.save(output_file, OF_IMAGE_QUALITY_BEST);
}

void CatalyseClass::draw() {
  ofBackground(100, 100, 100);
  if (show_render){
    finalFbo.draw(posX,posY);//,w/2,h/2);
    startFbo.draw(w+posX*2,posY,w/2,h/2);
    result.draw(w+posX*2,posY+h/2,w/2,h/2);
  }
  else {
    result.draw(posX,posY);//,w/2,h/2);
    startFbo.draw(w+posX*2,posY,w/2,h/2);
    finalFbo.draw(w+posX*2,posY+h/2,w/2,h/2);
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
    /*    else {
      finalPxls[i*3] = startPxls[i*3];
      finalPxls[(i*3)+1] = startPxls[(i*3)+1];
      finalPxls[(i*3)+2] = startPxls[(i*3)+2];
      }*/
  }
  finalFbo.getTexture().loadData(finalPxls);
}
//export_version_02_2324
void CatalyseClass::readImage(){//}string filePath, bool hasParam, int zeros, string main_dir, string format) {

  if (filePath != "") {
    //    format = ".png";
    succ = bild.load(main_dir+filePath+format);
    if (!succ) {
      filePath = ofToLower(filePath);
      succ = bild.load(main_dir+filePath+format);
    }
  };
  if (filePath == "" || !succ){
    //    format = ".jpg";
    string_nb_zeros = "";
    for (i = 0; i < nombre_zeros-log10((actualImage>0) ? actualImage : 1); ++i) {
      string_nb_zeros += "0";
    }
       
    succ = bild.load(input_dir + file_name + string_nb_zeros + to_string(actualImage) + format);
    if (!succ) {
      cerr << "Error when loading image...\n";
      std::exit(1);
    }
  }
  
  w = bild.getWidth();
  h = bild.getHeight();
  if ((w < ofGetWidth()/3) && (h < ofGetHeight()/3)) {
    w = w * 2;
    h = h * 2;
  }
  else if ((w > ofGetWidth()) || (h > ofGetHeight())) {
    w = w * 0.5;
    h = h * 0.5;
  }

  count = h * w;
  bild.resize(w,h);
  startImage = bild;
  
  delete[] rlife_board;
  delete[] sum_board;
  delete[] new_board;

  rlife_board = new bool[count];
  sum_board = new bool[count];
  new_board = new bool[count];

  result.clear();
  result.allocate(w, h, GL_RGB);

  bild.getTexture().readToPixels(pxls);
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

  finalFbo.getTexture().loadData(pxls);


  livingCell_count = 0;

  //    while (livingCell_count < livingCell_minValue) {
  livingCell_count = 0;
  if (double_threshold) {
    initStateFromImageBetweenTwoColors(pxls, if_white, threshold_min, threshold_max);
  }
  else {
    initStateFromImage(pxls, if_white, threshold);
  }

  // adding a first step with Classical rules
  // to do: adding a timeline:
  if (first_step_classical){
    updateBoardClassical();
  }

  for (i = 0; i < count; ++i) {
    if (rlife_board[i]) {
      livingCell_count++;
      result_pxls[i * 3] = 255;
      result_pxls[i * 3 + 1] = 255;
      result_pxls[i * 3 + 2] = 255;
    }
    else {
      result_pxls[i * 3] = 0;
      result_pxls[i * 3 + 1] = 0;
      result_pxls[i * 3 + 2] = 0;
    }
  }
  //}
  result.getTexture().loadData(result_pxls);
}

void CatalyseClass::initStateFromImage(ofPixels pxls, bool val, int threshold) {
  for (i = 0; i < count; ++i) {
    if (pxls[channel+(i * 3)] < threshold){
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
	result_pxls[i * 3] = 255 * (invert ? 1 : 0);
	result_pxls[i * 3 + 1] = 255 * (invert ? 1 : 0);
	result_pxls[i * 3 + 2] = 255 * (invert ? 1 : 0);
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


