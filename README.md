You may view the github repository of this code here:
https://github.com/DrMemezo/cs224_oop_hw3/


A few things to note:
1) The subtract function is not implemented yet.
2) I've opted to not allow angles to be created if it's ambigious where they will be placed
3) The shapes are referenced-counted, so if they cannot be deleted if they are 
being referenced

The UML diagrams is in the docs/ folder.

TO RUN THE CODE:
1) Have CMake installed and a g++ compiler of your choice.
2) create a 'build' folder in the root
3) Run `cmake -S . -B ./build`
4) Run `cmake --build build`
5) Once its done compiling, run `build/OOP_HW3.exe`

If there are any errors, please contact me.