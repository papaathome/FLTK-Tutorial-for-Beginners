
// example7.cpp
#include <FL/Fl.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Window.H>
constexpr const int W = 300;
constexpr const int H = 200;
constexpr const int M = 10;
void browser_cb(Fl_Widget *w) {
  Fl_Browser *b = (Fl_Browser *)w; // cast to get access to Browser methods
  // retrieve selected item from browser
  int index = b->value();
  // add text to browser using the retrieved index number
  if (index == 1) {
    b->add("You selected Line1");
  } else if (index == 2) {
    b->add("You selected Line2");
  } else if (index == 3) {
    b->add("You selected Line3");
  }
}
int fl_main(int argc, char **argv) {
  Fl_Window *win = new Fl_Window(W, H, "Browser Example");
  Fl_Browser *b = new Fl_Browser(M, 4 * M, win->w() - 2 * M, win->h() - 5 * M);
  b->type(FL_MULTI_BROWSER);
  b->add("Line1");
  b->add("Line2");
  b->add("Line3");
  b->callback(browser_cb);
  win->show();
  auto result = Fl::run();
  delete b;
  delete win;
  return result;
}

