
// example1.cpp
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
constexpr const int WIDTH = 400;
constexpr const int HEIGHT = 400;
int fl_main(int argc, char **argv) {
  // Create a window - width, height, label (=title)
  Fl_Window win(WIDTH, HEIGHT, "FLTK Tutorial - Example 1");
  // Display the window
  win.show();
  // Run and return
  return Fl::run();
}

