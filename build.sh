#! /usr/bin/bash
#
# build.sh - interface to cmake
#
# major: config  2026-09-17T14:34:11
# minor: version 2026-09-17T14:34:11

# local libraries location
LOCAL_LIB="~/lib"

# FLTK version to use
FLTK_VERSION="1.4.5"
#FLTK_VERSION="1.5"

# FLTK path (empty: use system wide instance).
#FLTK_DIR=""
FLTK_DIR="$LOCAL_LIB/packages/fltk/fltk-$FLTK_VERSION/build"

# CMake build location
CMAKE_BUILD_PATH="./build"

# CMake arguments
PACKAGE_CMAKE_ARGS="-DCMAKE_CXX_STANDARD=23"
PACKAGE_CMAKE_ARGS="$PACKAGE_CMAKE_ARGS -DCMAKE_CXX_STANDARD_REQUIRED=ON"
PACKAGE_CMAKE_ARGS="$PACKAGE_CMAKE_ARGS -DCMAKE_CXX_EXTENSIONS=OFF"
PACKAGE_CMAKE_ARGS="$PACKAGE_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=$LOCAL_LIB"

# no changes required below this line. ###########################################################

PACKAGE_CMAKE_ARGS="$PACKAGE_CMAKE_ARGS -DFLTK_VERSION=$FLTK_VERSION"
PACKAGE_CMAKE_ARGS="$PACKAGE_CMAKE_ARGS -DFLTK_DIR=$FLTK_DIR"

function extract_args() {
   local arg_first=1
   local args=

   for a in $@ ; do
       if [ $arg_first -eq 1 ]; then
           arg_first=0
       else
           args="$args $a"
       fi
   done
   if [ "$args" != "" ]; then
       CMAKE_ARGS="$args"
   fi
}

function launch_mk() {
    echo "cmake $@"
    cmake $@
}

function launch_tst() {
    pushd  "$CMAKE_BUILD_PATH"
    echo "ctest $@"
    ctest $@
    popd
}

function launch_pkg() {
    pushd $CMAKE_BUILD_PATH
    echo "cpack $@"
    cpack $@
    popd
}

if [ "$1" == "--generate" ]; then
    extract_args $@
    launch_mk "-S . -B $CMAKE_BUILD_PATH $PACKAGE_CMAKE_ARGS $CMAKE_ARGS"
elif [ "$1" == "--build" ]; then
    extract_args $@
    launch_mk "--build $CMAKE_BUILD_PATH $CMAKE_ARGS"
elif [ "$1" == "--test" ]; then
    extract_args $@
    launch_tst "$CMAKE_ARGS"
elif [ "$1" == "--install" ]; then
    extract_args $@
    launch_mk "--install $CMAKE_BUILD_PATH $CMAKE_ARGS"
elif [ "$1" == "--pack" ]; then
    extract_args $@
    launch_pkg "-B $CPACK_PACKAGE_DIRECTORY $CMAKE_ARGS"
else
    echo "./build.sh mode [arguments]"
    echo "bash build.sh mode [arguments]"
    echo ""
    echo "mode:"
    echo "--generate    start cmake for generating a build system."
    echo "--build       start cmake for building the targets."
    echo "--test        start ctest for test targets."
    echo "--install     start cmake for installing."
    echo "--pack        start cpack for building a package."
    echo ""
    echo "arguments     list of arguments copied verbatum to cmake."
    echo ""
    echo "Assumed settings:"
    echo "The first part of this script contains dependencies configuration."
    echo "Check the configuration before attemting to generate or build."
    echo ""
    echo "Examples:"
    echo "This will recreate a build system from scratch."
    echo "build.sh --generate --fresh"
    echo ""
    echo "This will build all targets (except documentaton)."
    echo "build.sh --build --config Release"
    echo ""
    echo "This will rebuild all targets from scratch (except documentation)."
    echo "build.sh --build --clean-first"
    echo ""
    echo "This will build only the manual."
    echo "build.sh --build --target manual"
    echo ""
    echo "This will build only the man pages"
    echo "build.sh --build --target manpages"
    echo ""
    echo "This will run all tests (tester must manualy close all window forms)."
    echo "build.sh --test"
    echo ""
    echo "This will run all tests, with output for failing tests."
    echo "build.sh --test --output-on-failure"
    echo ""
fi

