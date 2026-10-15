
// example8.cpp
#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Window.H>
constexpr const int WIDTH = 420;
constexpr const int HEIGHT = 280;
Fl_Window *win = nullptr;
void Menu_CB_Open(Fl_Widget *w, void *) { win->label("Open selected"); }
void Menu_CB_Save(Fl_Widget *w, void *) { win->label("Save selected"); }
void Menu_CB_Quit(Fl_Widget *w, void *) { win->label("Quit selected"); }
void Menu_CB_Help(Fl_Widget *w, void *) { win->label("Help selected"); }
int fl_main(int argc, char **argv) {
  // Open the application window and menu bar with callbacks
  win = new Fl_Window(WIDTH, HEIGHT);
  win->color(FL_WHITE);
  // implicit: win->begin();
  Fl_Menu_Bar *menubar = new Fl_Menu_Bar(0, 0, win->w(), 25);
  menubar->add("&File/&Open", 0, Menu_CB_Open);
  menubar->add("&File/&Save", 0, Menu_CB_Save);
  menubar->add("&File/&Quit", 0, Menu_CB_Quit);
  menubar->add("&Help", 0, Menu_CB_Help);
  win->end();
  win->show();
  auto result = Fl::run();
  delete win;
  win = nullptr;
  return result;
}

