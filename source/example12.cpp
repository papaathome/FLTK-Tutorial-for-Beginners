
// example12.cpp
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Shared_Image.H>
#include <stdio.h>
#include <stdlib.h>
constexpr const int WIDTH = 500;
constexpr const int HEIGHT = 400;
constexpr const char *JPGFILE = "jolly.jpg"; // any .jpg (500 x 400)px will do.
int fl_main(int argc, char **argv) {
  fl_register_images();
  Fl_Double_Window win(WIDTH, HEIGHT, "Example image viewer with scrollbars");
  win.color(FL_WHITE);
  win.begin();
  Fl_Scroll scr(0, 0, WIDTH, HEIGHT);
  Fl_JPEG_Image jpg(JPGFILE);
  if (jpg.h() == 0) {
    // error check failed.
    perror(JPGFILE);
    exit(1);
  }
  Fl_Box box(0, 0, jpg.w(), jpg.h());
  win.end();
  box.image(jpg);
  win.resizable(win);
  win.show();
  return (Fl::run());
}

