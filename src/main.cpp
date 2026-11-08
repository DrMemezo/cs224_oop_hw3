#include <iostream>
#include <sstream>
using namespace std;

#include "Canvas.hpp"
constexpr int CANVAS_WIDTH = 40; 

int main () {
  
  Canvas canvas(CANVAS_WIDTH);

  string line;
  while (getline(cin, line)) {
    istringstream inp_str(line);
    string cmd;
    if (!(inp_str >> cmd)) continue; // Skip empty line

    if (cmd == "point") {
      int x, y;
      if (!(inp_str >> x >> y)) {
        cerr << "USAGE: point [x] [y]" << endl;
        continue;
      }

      cout << "Point at: " << x << ", " << y << endl;
    }
    else if (cmd == "quit") {break;}

    else {
      // TODO: Help message here
      cout << "display help here" << endl;
    }

  } 
   

  return 0;
}
