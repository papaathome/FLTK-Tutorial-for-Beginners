
// example2.cpp
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
constexpr const int WIDTH = 340;
constexpr const int HEIGHT = 180;
int fl_main(int argc, char **argv) {
  // Create a window - width, height, label (=title)
  Fl_Window *win = new Fl_Window(WIDTH, HEIGHT, "FLTK Tutorial - Example 2");
  // Set color of window to white
  win->color(FL_WHITE);
  // Begin adding children to this window
  win->begin(); // recomended habit: intent between begin() and end()
  // Create a button - x , y , width, height, label.
  // Implicit: win takes ownership of button1.
  Fl_Button *button1 = new Fl_Button(25, 15, 140, 40, "OK");
  // Set color of button to red
  button1->color(FL_RED);
  // Stop adding children to this window
  win->end();
  // Display the window
  win->show();
  // Run and return
  auto result = Fl::run();
  // clean up.
  delete win; // implicit: also delete button1.
  return result;
}

