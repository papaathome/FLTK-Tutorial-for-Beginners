
// example5.cpp
#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Window.H>
constexpr const int WIDTH = 300;
constexpr const int HEIGHT = 90;
// Fl_Input input1(90, 10, 180, 20, "Input : "); // will fail
// Fl_Output output1(90, 40, 180, 20, "Output : "); // will fail
Fl_Input *input1 = nullptr;
Fl_Output *output1 = nullptr;
static void cb_input1(Fl_Input *, void *userdata) {
  input1->label((const char *)userdata);
  output1->value(input1->value());
  input1->value(""); // clear again
}
int fl_main(int argc, char **argv) {
  Fl_Window win(WIDTH, HEIGHT, "Example for Input and Output boxes");
  win.begin();
  // win will take ownership of *input1;
  // win.add(input1); will fail during cleanup of win.
  input1 = new Fl_Input(90, 10, 180, 20, "Input : ");
  input1->callback((Fl_Callback *)cb_input1, (void *)"Enter next:");
  input1->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);
  // win will take ownership of *output1;
  // win.add(output1); will fail during cleanup of win.
  output1 = new Fl_Output(90, 40, 180, 20, "Output : ");
  win.end();
  win.show();
  // cleanup of win: delete *input1 which fails with an application termination
  // if it points to a static instance. (can't delete a static instance)
  return Fl::run();
}

