
// aim: facilitate loader entry point for Boost unit testing.
//      unit testing is to be done in separate code files.

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#define TRACE_PREFIX "main_test()"
#include "tracer.h"

extern int fl_main(int argc, char ** argv);

struct FixtureExample {
    FixtureExample () { }

    ~FixtureExample() { }

    void setup() { }

    void teardown() { }
};

BOOST_FIXTURE_TEST_SUITE(Example, FixtureExample);

BOOST_AUTO_TEST_CASE(boot) {
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
    BOOST_CHECK(result == 0);
    BOOST_CHECK(have_exception == false);
    
    log("OK");
}

BOOST_AUTO_TEST_SUITE_END();


