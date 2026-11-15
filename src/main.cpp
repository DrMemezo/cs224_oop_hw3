#include <iostream>
#include <sstream>
#include <string_view>
#include <stdexcept>
using namespace std;

#include "Canvas.hpp"
constexpr int CANVAS_WIDTH = 40; 

constexpr std::string_view HELP_MESSAGE = R"DELIM(
  point [x] [y]     ---- Creates a point at (x, y). the origin is at the top left corner
  combine id1 id2   ---- Combines shapes with the respective ids into a bigger shape if possible
  sub id1 id2       ---- Subtract id2 shape from id1
  mirror line       ---- Mirror a triangle alone the given line
  del id            ---- Deletes the shape with given id
  clear             ---- Clears the canvas of all the shapes
  history           ---- Display a history of the shapes in memory
  render            ---- Renders the canvas
  quit              ---- Quit the application
  help              ---- Render this message
)DELIM";


void print_help_message() {
  cout << HELP_MESSAGE << endl;
}

int main () {
  
  Canvas canvas(CANVAS_WIDTH);

  print_help_message();

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

      if ( !( canvas.addPoint(x, y) ) ) {
        cerr << "Point could not be created!" << endl;
        continue;
      }
      

      cout << "Point at: " << x << ", " << y << endl;
    }

    else if (cmd == "combine") {
      int id1, id2;
      if (!(inp_str >> id1 >> id2)) {
        cerr << "USAGE: combine [id1] [id2]" << endl;
        continue;
      }

      int new_id;
      try {
        new_id = canvas.combine(id1, id2);
      }
      catch (const std::invalid_argument& e) {
        std::cerr << "ERR: " << e.what() << endl;
        continue;
      }

      cout << "Created new shape with id: " << new_id << endl;
    }
    else if (cmd == "sub") {throw runtime_error("oops i hortoned");}
    else if (cmd == "mirror") {throw runtime_error("oops i hortoned");}
    else if (cmd == "del") {throw runtime_error("oops i hortoned");}
    else if (cmd == "clear") {
      canvas.clear();
      cout << "Cleared successfully" << endl;
    }

    else if (cmd == "history") {
      canvas.show_history();
    }

    else if (cmd == "render") {
      canvas.render();
    }

    else if (cmd == "debug") {
      int id_;
      if (!(inp_str >> id_)) {
        cerr << "LMAAOOOOO THIS GUY DOESNT KNOW BALL" << endl;
        continue;
      }

      try {
        canvas.debug(id_);
      }
      catch (const std::invalid_argument& e) {
        cerr << "ERR: " << e.what() << endl;
        continue;
      }

    }
    else if (cmd == "quit") {break;}

    else {
      print_help_message();
    }

  } 
   

  return 0;
}
