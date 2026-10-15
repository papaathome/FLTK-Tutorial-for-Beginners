cmake_minimum_required ( VERSION 3.31.6...4.2.1 )

### CMake project ############################################################### {{{1

project(
    "FLTK-Tutorial"
    VERSION 0.1.0
    DESCRIPTION "FLTK Tutorial supplement, build example sources."
    LANGUAGES CXX)
set(PROJECT_DATE "2026/09/18")

set(APP_CXX_STANDARD          "23")  # used if CMAKE_CXX_STANDARD is empty.
set(APP_CXX_STANDARD_REQUIRED "ON")  # used if CMAKE_CXX_STANDARD_REQUIRED is empty
set(APP_CXX_EXTENSIONS        "OFF") # used if CMAKE_CXX_EXTENSIONS is empty

set(APP_DEBUG                 OFF)   # ON will switch on reporting details for everything.
set(APP_TESTING_ENABLED       ON )   # enable/diable ctest configuration.

set(FLTK_LIB                  "1.4.5") # used if FLTK_VERSION is empty. note: supply FLTK_DIR for non-standard locations.
set(report_Fltk_details       OFF )

if (${APP_TESTING_ENABLED})
    enable_testing()
endif()

include(cmake/project-support.cmake)
include(GNUInstallDirs)

### shared compiler settings ##################################################### {{{2

set(BUILD_SHARED_LIBS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# interprocedural optimazation.
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMAZATION ${ipo_supported})

if (MSVC)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

  # Enable Hot Reload for MSVC compilers if supported.
  set ( CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>" )
endif()

add_library(compiler_flags INTERFACE)

if (NOT DEFINED CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD STREQUAL "")
    set(CMAKE_CXX_STANDARD ${APP_CXX_STANDARD})
endif()
target_compile_features(compiler_flags INTERFACE "cxx_std_${CMAKE_CXX_STANDARD}")

if (NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED OR CMAKE_CXX_STANDARD_REQUIRED STREQUAL "")
    set(CMAKE_CXX_STANDARD_REQUIRED ${APP_CXX_STANDARD_REQUIRED})
endif()

if (NOT DEFINED CMAKE_CXX_EXTENSIONS OR CMAKE_CXX_EXTENSIONS STREQUAL "")
    set(CMAKE_CXX_EXTENSIONS ${APP_CXX_EXTENSIONS})
endif()

# compiler arguments
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(
    compiler_flags INTERFACE

    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wunused;-Wfatal-errors;-fno-diagnostics-show-caret>>"

    # MSVC -Wall will procude warnings on MSVC headers (?!)
    "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4;/Zc:__cplusplus>>")

### using external libraries #################################################### {{{2

set(report_Boost_details     OFF)

include(CMakePrintHelpers)
include(FetchContent)

if (NOT DEFINED FLTK_VERSION OR FLTK_VERSION STREQUAL "")
    set(APP_FLTK ${FLTK_LIB})
endif()

# see: https://www.fltk.org/index.php
# see: https://github.com/fltk/fltk
find_package(FLTK ${FLTK_VERSION} CONFIG REQUIRED)
if (report_Fltk_details OR APP_DEBUG)
    cmake_print_properties(
        TARGETS
            fltk::fltk
            #fltk::forms   # Use on specific needs
            #fltk::gl      # Use on specific needs
            #fltk::images  # Use on specific needs
            #fltk::jpeg    # Not available by default
            #fltk::png     # Not available by default
            #fltk::z       # Not available by default
        PROPERTIES TYPE SOURCE_DIR INTERFACE_INCLUDE_DIRECTORIES)
endif()

### Application ################################################################## {{{2

add_subdirectory(source)

# vim: foldlevel=1

