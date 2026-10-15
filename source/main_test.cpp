
#define TRACE_PREFIX "main_test()"
#include "tracer.h"

extern int fl_main(int argc, char ** argv);

int main(int argc, char ** argv) {
    // prepare
    int result{ 0 };
    
    bool have_exception{ false };
    try {
        // test
        log("test: testing");
        result = fl_main(0, nullptr);
    }
    catch (...) {
        log("test: exception");
        have_exception = true;
        result = -1;
    }
    log(result);

    // assert
    log("test: assert");
    auto r = 0;
    if (result != 0) r = 1;
    if (have_exception != false) r = 1;
    
    log(((r == 0) ? "OK" : "failing"));
    return r;
}

