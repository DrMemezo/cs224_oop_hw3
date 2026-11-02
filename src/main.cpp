#include <iostream>
using namespace std;


#include "Canvas.hpp"
constexpr int CANVAS_WIDTH = 40; 

int main () {

  Canvas canvas(CANVAS_WIDTH);
  canvas.display();


  return 0;
}
