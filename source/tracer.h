
// definitions for tracing.
#pragma once

#define build_verbose 1

#if build_verbose
#    if !defined(TRACE_PREFIX)
#        define TRACE_PREFIX "FLTK"
#    endif
#    include <thread>
#    include <iostream>
#    define log(msg) std::cout << timestamp() << " " << std::this_thread::get_id() << " " << TRACE_PREFIX << ": " << msg << std::endl
#else
#    define log(msg) // ignore
#endif

#if build_verbose

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

template <bool use_msec = true>
std::string _timestamp(const char * fmt, bool add_msec = use_msec) {
    using namespace std::chrono;
    
    const auto current_time_point {system_clock::now()};
    const auto current_time {system_clock::to_time_t (current_time_point)};
    const auto current_localtime {*std::localtime (&current_time)};
    const auto current_time_since_epoch {current_time_point.time_since_epoch()};
    const auto current_milliseconds {duration_cast<milliseconds> (current_time_since_epoch).count() % 1000};
    
    std::ostringstream stream;
    stream << std::put_time (&current_localtime, fmt);
    if (add_msec) {
        stream << "." << std::setw (3) << std::setfill ('0') << current_milliseconds;
    }
    return stream.str();
}

template <bool use_msec = true>
std::string timestamp() { return _timestamp("%T", true); }

template <bool use_msec = true>
std::string datetimestamp() { return _timestamp("%FT%T", true); }


#endif // build_verbose

