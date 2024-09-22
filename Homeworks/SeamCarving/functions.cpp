#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
  // TODO: implement (part 1)
  std::ifstream file;
  file.open(filename);
  string type;
  int max;

  if (!file.is_open()) {
    throw std::runtime_error("Failed to open " + filename);
  }

  file >> type;
  if (type != "p3" && type != "P3") {
    throw std::runtime_error("Invalid type " + type);
  }

  file >> width >> height >> max;
  if (width <= 0 || width > MAX_WIDTH || height <= 0 || height > MAX_HEIGHT) {
    throw std::runtime_error("Invlaid dimensions");
  }

  Pixel pixel;
  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {

      file >> pixel.r;
      file >> pixel.g;
      file >> pixel.b;
      if (file.fail()) {
        throw std::runtime_error("Invalid color value");
      }

      if (pixel.r < 0 || pixel.g < 0 || pixel.b < 0 || pixel.r > max || pixel.g > max || pixel.b > max) {
        throw std::runtime_error("Invalid color value");
      }
      image[j][i] = pixel;
    }
  }
  int test;
  file >> test;
  if (!file.fail()) {
    throw std::runtime_error("Too many values");
  }
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {

  std::ofstream fileout;
  fileout.open(filename);

  if (!fileout.is_open()) {
    throw std::runtime_error("Failed to open " + filename);
  }

  fileout << "P3" << endl;
  fileout << width << " " << height << endl;
  fileout << 255 << endl;

  for (unsigned int i = 0; i < height; i++) {
    for (unsigned int j = 0; j < width; j++) {
      fileout << image[j][i].r << " " << image[j][i].g << " " << image[j][i].b << endl;
    }
  }
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  // TODO: implement (part 1)
  int xupper = x + 1;
  int xlower = x - 1;
  int yupper = y + 1;
  int ylower = y - 1;
  if (x == 0) {
    xlower = width - 1;
  }
  if (x == width-1) {
    xupper = 0;
  }
  if (y == 0) {
    ylower = height - 1;
  }
  if (y == height-1) {
    yupper = 0;
  }

  unsigned int xgradient = std::pow((image[xupper][y].r - image[xlower][y].r),2) + std::pow((image[xupper][y].g - image[xlower][y].g),2) + std::pow((image[xupper][y].b - image[xlower][y].b),2);
  unsigned int ygradient = std::pow((image[x][yupper].r - image[x][ylower].r),2) + std::pow((image[x][yupper].g - image[x][ylower].g),2) + std::pow((image[x][yupper].b - image[x][ylower].b),2);
  return xgradient + ygradient;
}

// uncomment functions as you implement them (part 2)

unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
  // TODO: implement (part 2)
  unsigned int curr_col = start_col;
  unsigned int energy1;
  unsigned int energy2;
  unsigned int energy3;
  unsigned int total_energy = 0;
  seam[0] = start_col;

  for (unsigned int row = 0; row < MAX_HEIGHT - 1; row++) {
    if (curr_col == 0) {
      energy1 = energy(image, curr_col, row + 1, width, height);
      energy2 = energy(image, curr_col + 1, row + 1, width, height);

      if (energy1 > energy2) {
        curr_col++;
      }
    }
    else if (curr_col == width-1) {
      energy1 = energy(image, curr_col - 1, row + 1, width, height);
      energy2 = energy(image, curr_col, row + 1, width, height);

      if (energy1 < energy2) {
        curr_col--;
      }
    }
    else {
      energy1 = energy(image, curr_col - 1, row + 1, width, height);
      energy2 = energy(image, curr_col, row + 1, width, height);
      energy3 = energy(image, curr_col + 1, row + 1, width, height);

      if (energy1 < energy2 && energy1 < energy3) {
        curr_col--;
      }
      else if (energy3 < energy1 && energy3 < energy2) {
        curr_col++;
      }
      else if (energy1 == energy3 && energy1 < energy2) {
        curr_col++;
      }
    }
    seam[row + 1] = curr_col;
  }

  for (unsigned int i = 0; i < height; i++) {
    total_energy += energy(image, seam[i], i, width, height);
  } 
  return total_energy;
}

unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
  unsigned int curr_row = start_row;
  unsigned int energy1;
  unsigned int energy2;
  unsigned int energy3;
  unsigned int total_energy = 0;
  seam[0] = start_row;

  for (unsigned int col = 0; col < MAX_WIDTH - 1; col++) {
    if (curr_row == 0) {
      energy1 = energy(image, col + 1, curr_row, width, height);
      energy2 = energy(image, col + 1, curr_row + 1, width, height);

      if (energy1 > energy2) {
        curr_row++;
      }
    }
    else if (curr_row == height-1) {
      energy1 = energy(image, col + 1, curr_row - 1, width, height);
      energy2 = energy(image, col + 1, curr_row, width, height);

      if (energy1 < energy2) {
        curr_row--;
      }
    }
    else {
      energy1 = energy(image, col + 1, curr_row - 1, width, height);
      energy2 = energy(image, col + 1, curr_row, width, height);
      energy3 = energy(image, col + 1, curr_row + 1, width, height);

      if (energy1 < energy2 && energy1 < energy3) {
        curr_row--;
      }
      else if (energy3 < energy1 && energy3 < energy2) {
        curr_row++;
      }
      else if (energy1 == energy3 && energy1 < energy2) {
        curr_row--;
      }
    }
    seam[col + 1] = curr_row;
  }

  for (unsigned int i = 0; i < width; i++) {
    total_energy += energy(image, i, seam[i], width, height);
  } 
  return total_energy;
}

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  unsigned int minSeamIndex = 0;
  unsigned int minSeamEnergy = loadVerticalSeam(image, 0, width, height, seam);
  unsigned int currSeamEnergy;
  for (unsigned int col = 1; col < width; col++) {
    currSeamEnergy = loadVerticalSeam(image, col, width, height, seam);
    if (currSeamEnergy < minSeamEnergy) {
      minSeamEnergy = currSeamEnergy;
      minSeamIndex = col;
    }
  }
  loadVerticalSeam(image, minSeamIndex, width, height, seam);
}

void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  unsigned int minSeamIndex = 0;
  unsigned int minSeamEnergy = loadHorizontalSeam(image, 0, width, height, seam);
  unsigned int currSeamEnergy;
  for (unsigned int row = 1; row < height; row++) {
    currSeamEnergy = loadHorizontalSeam(image, row, width, height, seam);
    if (currSeamEnergy < minSeamEnergy) {
      minSeamEnergy = currSeamEnergy;
      minSeamIndex = row;
    }
  }
  loadHorizontalSeam(image, minSeamIndex, width, height, seam);
}

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
  width--;
  for (unsigned int row = 0; row < height; row++) {
    for (unsigned int col = verticalSeam[row]; col < width; col++) {
      image[col][row] = image[col + 1][row];
    }
  }
}

void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
  height--;
  for (unsigned int col = 0; col < width; col++) {
    for (unsigned int row = horizontalSeam[col]; row < height; row++) {
      image[col][row] = image[col][row + 1];
    }
  }
}
