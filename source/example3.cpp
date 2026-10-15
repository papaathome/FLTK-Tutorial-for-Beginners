
// example3.cpp
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
constexpr const int WIDTH = 340;
constexpr const int HEIGHT = 180;
class MyWindow : public Fl_Window {
public:
  MyWindow(int width, int height, const char *title = 0)
      : Fl_Window(width, height, title) {
    // Set color of window to white
    color(FL_WHITE);
    // Begin adding children to this window
    begin();
    // Create a button - x , y , width, height, label
    // Implicit: this instance parent takes ownership of button1.
    Fl_Button *button1 = new Fl_Button(25, 15, 140, 40, "OK");
    // Set color of button to red
    button1->color(FL_RED);
    // Stop adding children to this window
    end();
    // Display the window
    show();
  }
};
int fl_main(int argc, char **argv) {
  // Create a window with our new class - width, height, label (=title)
  MyWindow win(WIDTH, HEIGHT, "FLTK Tutorial - Example 2++");
  // Run and return, implicit cleanup of win.
  return Fl::run();
}

