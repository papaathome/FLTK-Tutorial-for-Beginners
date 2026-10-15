
// example10.cpp
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Window.H>
#include <cstdint>
constexpr const int WIDTH = 300;
constexpr const int HEIGHT = 250;
class Dialog_Window : public Fl_Window {
public:
  int status;
  int radio;
  static Dialog_Window *dw_this;
  static void cb_button(Fl_Widget *w, void *d);
  static void cb_radio(Fl_Widget *b, void *d);
  Dialog_Window(int xpos, int ypos, int width, int height,
                const char *title = 0)
      : Fl_Window(xpos, ypos, width, height, title) {
    dw_this = this;
    color(FL_WHITE);
    begin(); // Begin adding children to this window
    Fl_Group *rb_group = new Fl_Group(15, 10, 105, 105);
    // implicit: rg_group->begin();
    rb_group->box(FL_UP_FRAME);
    {
      Fl_Round_Button *rb1 = new Fl_Round_Button(20, 15, 70, 30, "&Coffee");
      rb1->type(102);
      rb1->down_box(FL_ROUND_DOWN_BOX);
      rb1->callback(cb_radio, (void *)1);
    }
    {
      Fl_Round_Button *rb2 = new Fl_Round_Button(20, 45, 70, 30, "&Espresso");
      rb2->type(102);
      rb2->down_box(FL_ROUND_DOWN_BOX);
      rb2->callback(cb_radio, (void *)2);
    }
    {
      Fl_Round_Button *rb3 = new Fl_Round_Button(20, 75, 70, 30, "Ca&ppucino");
      rb3->type(102);
      rb3->down_box(FL_ROUND_DOWN_BOX);
      rb3->callback(cb_radio, (void *)3);
    }
    rb_group->end();
    Fl_Button *button_ok = new Fl_Button(10, 150, 80, 40, "OK");
    Fl_Button *button_c = new Fl_Button(110, 150, 80, 40, "Cancel");
    button_ok->callback(cb_button, (void *)1);
    button_c->callback(cb_button, (void *)2);
    end();
    set_modal();
    show();
  }
};
Dialog_Window *Dialog_Window::dw_this = NULL;
void Dialog_Window::cb_radio(Fl_Widget *b, void *d) {
  char msg[64];
  dw_this->radio = static_cast<int>(reinterpret_cast<intptr_t>((d)));
  sprintf(msg, "Radio Button: %d", dw_this->radio);
  dw_this->label(msg);
}
void Dialog_Window::cb_button(Fl_Widget *w, void *d) {
  dw_this->hide();
  dw_this->status = static_cast<int>(reinterpret_cast<intptr_t>((d)));
}
void cb_file(Fl_Widget *w, void *data) {
  Fl_Window *parent = static_cast<Fl_Window *>(data);
  parent->label("Please enter data now");
  // side effect: dw .ctor calls show() and is modal. (compiler may warn for
  // unused var)
  Dialog_Window *dw =
      new Dialog_Window(parent->x() + 20, parent->y() + 20, 200, 200, NULL);
}
int fl_main(int argc, char **argv) {
  Fl_Window win(WIDTH, HEIGHT, "FLTK Dialog Window Example");
  win.color(FL_WHITE);
  win.begin();
  Fl_Menu_Bar menubar(0, 0, win.w(), 25);
  menubar.add("&Coffee", 0, cb_file, (void *)&win);
  win.end();
  win.show();
  return Fl::run();
}

