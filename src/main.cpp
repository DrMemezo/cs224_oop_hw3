#include <iostream>
using namespace std;


#include "Canvas.hpp"
#include "Grid.hpp"
constexpr int CANVAS_WIDTH = 40; 

int main () {
  
  Grid g(40, 80);
  cout << "Empty" << endl;
  g.display();


  g.update(0, 0, '0');
  g.update(5, 5, '0');
  g.update(10, 5, '0');
  cout << "with in the corner" << endl;
  g.display();
  cout << g.getCell(10, 5) << endl;

  g.clear();

  cout << "Reset"<< endl;
  g.display();
  

  return 0;
}
