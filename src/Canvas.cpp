#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

#include "Canvas.hpp"

Canvas::Canvas(int width) 
{
    if (width < 0) {
        throw std::invalid_argument("Width cannot be negative.");
    }

    this -> width = width;
    height = width * 2;

    data = new char*[height];
    for (int i=0; i < height; i++) {
        data[i] = new char[width + 1]; // +1 for terminating byte
        for (int j=0; j < width; j++) {
            data[i][j] = ' ';
        }
        data[i][width] = '\0';
    }  
};

void Canvas::destroy() {
    for (int i=0; i < height; i++) delete [] data[i];
    delete [] data;
}

Canvas::~Canvas() {
    destroy();
} 


void Canvas::display() const {

  for (int i=0; i < width + 2; i++) cout << "-";
  cout << endl;

  for (int i = 0; i < height; i++) {
    cout << "|"
    << data[i] << "|" << endl;
  }

  for (int i=0; i < width + 2; i++) cout << "-";
  cout << endl;
}