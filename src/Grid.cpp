#include "Grid.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

Grid::Grid(int width, int height)
    : _data(nullptr), _width(width), _height(height)
{
    if (width < 0) throw invalid_argument("Width cannot be negative");
    if (height < 0) throw invalid_argument("Height cannot be negative");


    _data = new char*[height];
    for (int i=0; i < height; i++) {
        _data[i] = new char[width + 1]; // +1 for terminating byte
        for (int j=0; j < width; j++) {
            _data[i][j] = ' ';
        }
        _data[i][width] = '\0';
    }  

}

void Grid::clear() {
    for (int i=0; i < _height; i++) {
        for (int j=0; j < _width; j++) {
            _data[i][j] = ' ';
        }
    }  

}
void Grid::display() const {
  for (int i=0; i < _width + 2; i++) cout << "-";
  cout << endl;

  for (int i = 0; i < _height; i++) {
    cout << "|"
    << _data[i] << "|" << endl;
  }

  for (int i=0; i < _width + 2; i++) cout << "-";
  cout << endl;
}
void Grid::update(int x, int y, char cell) {
    if (x < 0 || x >= _width) return;
    if (y < 0 || y >= _height) return;

    _data[y][x] = cell;
}

char Grid::getCell(int x, int y) const {
    if (x < 0 || x >= _width) throw invalid_argument("Invalid X");
    if (y < 0 || y >= _height) throw invalid_argument("Invalid Y");

    return _data[y][x];
}
Grid::~Grid() {
    for (int i=0; i < _height; i++) delete [] _data[i];
    delete [] _data;
}