
// example11.cpp
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Window.H>
constexpr const int WIDTH = 500;
constexpr const int HEIGHT = 400;
constexpr const int MARGIN = 10;
constexpr const char *PNGFILE = "jolly.png"; // any .png (500 x 400)px will do.
int fl_main(int argc, char **argv) {
  fl_register_images();         // initialize image lib
  Fl_Window win(WIDTH, HEIGHT); // make a window
  Fl_Box box(MARGIN, MARGIN, WIDTH - 2 * MARGIN, HEIGHT - 2 * MARGIN);
  // widget that will contain the image
  Fl_PNG_Image png(PNGFILE); // load png image into ram
  box.image(png);            // attach png image to box
  win.show();
  return (Fl::run());
}

