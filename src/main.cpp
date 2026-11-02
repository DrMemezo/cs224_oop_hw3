#include <iostream>
using namespace std;

constexpr int CANVAS_WIDTH = 40; 
constexpr int CANVAS_HEIGHT = CANVAS_WIDTH * 2; 

int main () {

  constexpr int TERM_WIDTH = CANVAS_WIDTH + 2;
  constexpr int TERM_HEIGHT = CANVAS_HEIGHT + 2;
  char canvas[TERM_WIDTH][TERM_HEIGHT] = {};

  for (int i=0; i < CANVAS_WIDTH + 2; i++) {
    canvas[i][0] = '|';
    for (int j=1; j <= CANVAS_HEIGHT; j++) canvas[i][j] = ' ';
    canvas[i][CANVAS_HEIGHT + 1] = '|';

  }

  for (int i=0; i < CANVAS_HEIGHT + 2; i++) {
    canvas[0][i] = '-';
    canvas[CANVAS_WIDTH + 1][i] = '-';

  }

  for (int i = 0; i < CANVAS_WIDTH + 2; i++) {
    cout << canvas[i] << endl;
  }

  cout << "Hello World!" << endl;
  return 0;
}
