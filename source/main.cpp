
// aim: separate all application code from loader entry point.
//      this will enable full unit testing of the application code.

#define TRACE_PREFIX "main()"
#include "tracer.h"

/** \brief @fn fl_main: forward declaration to open the FLTK main form */
extern int fl_main(int argc, char **argv);

/** \brief boot process hook, jump to fl_main() */
int main(int argc, char **argv) {
    int result = 0;
    try { // limitation: catch exceptions in this thread only.
        log("open FLTK main form");
        result = fl_main(argc, argv);
        log("OK");
    }
    catch (...) {
        result = -1;
        log("Exception");
    }
    log(result);
    return result;
}

