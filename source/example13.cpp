
// example13.cpp
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>
constexpr const int W = 400;
constexpr const int H = 200;
constexpr const int M = 10;
int fl_main(int argc, char **argv) {
  Fl_Window *win = new Fl_Window(W, H, "Tabs Example");
  {
    // implicit: win->begin();
    Fl_Tabs *tabs = new Fl_Tabs(M, M, W - 2 * M, H - 2 * M);
    {
      // implicit: tabs->begin();
      // A tab
      Fl_Group *aaa =
          new Fl_Group(M, 3 * M + 5, W - 2 * M, H - 4 * M - 5, "A-Buttons");
      {
        // implicit: aaa->begin();
        Fl_Button *b1 = new Fl_Button(50, 60, 90, 25, "Button A1");
        b1->color(88 + 1);
        Fl_Button *b2 = new Fl_Button(50, 90, 90, 25, "Button A2");
        b2->color(88 + 2);
        Fl_Button *b3 = new Fl_Button(50, 120, 90, 25, "Button A3");
        b3->color(88 + 3);
      }
      aaa->end();
      // B tab
      Fl_Group *bbb =
          new Fl_Group(M, 3 * M + 5, W - 2 * M, H - 4 * M - 5, "B-Buttons");
      {
        // implicit: bbb->begin();
        Fl_Button *b1 = new Fl_Button(50, 60, 90, 25, "Button B1");
        b1->color(88 + 1);
        Fl_Button *b2 = new Fl_Button(150, 60, 90, 25, "Button B2");
        b2->color(88 + 3);
        Fl_Button *b3 = new Fl_Button(250, 60, 90, 25, "Button B3");
        b3->color(88 + 5);
      }
      bbb->end();
    }
    tabs->end();
  }
  win->end();
  win->show();
  return (Fl::run());
}

