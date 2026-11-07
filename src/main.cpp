#include <iostream>
using namespace std;


#include "Grid.hpp"
constexpr int CANVAS_WIDTH = 40; 

int main () {
  
  Grid g(40, 80);
  cout << "Empty" << endl;
  g.display();


  g.setCell(0, 0, '0');
  g.setCell(5, 5, '0');
  g.setCell(10, 5, '0');
  cout << "with in the corner" << endl;
  g.display();
  cout << g.getCell(10, 5) << endl;

  g.clear();

  cout << "Reset"<< endl;
  g.display();
  

  return 0;
}
