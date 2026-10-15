
// example6.cpp
#include <FL/Fl.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Window.H>
constexpr const int WIDTH = 400;
constexpr const int HEIGHT = 200;
int fl_main(int argc, char **argv) {
  Fl_Window *win = new Fl_Window(WIDTH, HEIGHT);
  Fl_Text_Buffer *buff = new Fl_Text_Buffer();
  Fl_Text_Editor *disp = new Fl_Text_Editor(20, 20, 360, 160, "Editor Window");
  disp->buffer(buff);
  win->resizable(*disp);
  win->show();
  buff->text("FLTK Tutorial"); // add initial text here if required
  auto result = Fl::run();
  return result;
}

