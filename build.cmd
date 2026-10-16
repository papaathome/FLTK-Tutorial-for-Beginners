@echo off
::
:: build.cmd - interface to cmake.exe
::
:: config  2026-09-17T14:34:11
:: version 2026-10-16T09:23:01

setlocal enabledelayedexpansion

:: local libraries location
set LOCAL_LIB=C:/home/andre/lib

:: FLTK version to use
set FLTK_VERSION=1.4.5
::set FKTK_VERSION=1.5

:: FLTK path (empty: use system wide instance).
::set FLTK_DIR=
set FLTK_DIR=C:/home/andre/development/_lib/FLTK/fltk-%FLTK_VERSION%/build

:: CMake build location
if "%CMAKE_BUILD_PATH%"=="" set CMAKE_BUILD_PATH=./build

:: CMake arguments
set PACKAGE_CMAKE_ARGS=-DCMAKE_CXX_STANDARD=23
set PACKAGE_CMAKE_ARGS=%PACKAGE_CMAKE_ARGS% -DCMAKE_CXX_STANDARD_REQUIRED=ON
set PACKAGE_CMAKE_ARGS=%PACKAGE_CMAKE_ARGS% -DCMAKE_CXX_EXTENSIONS=OFF
set PACKAGE_CMAKE_ARGS=%PACKAGE_CMAKE_ARGS% -DCMAKE_INSTALL_PREFIX=%LOCAL_LIB%

:: no changes required below this line. ::::::::::::::::::::::::::::::::::::::::::::::::::::::::

set CMAKE=cmake.exe
set CTEST=ctest.exe
set CPACK=cpack.exe

set PACKAGE_CMAKE_ARGS=%PACKAGE_CMAKE_ARGS% -DFLTK_VERSION=%FLTK_VERSION%
set PACKAGE_CMAKE_ARGS=%PACKAGE_CMAKE_ARGS% -DFLTK_DIR=%FLTK_DIR%

if "%~1"=="--generate" (
    set CMD=%CMAKE%
    set ARGS=-S . -B "%CMAKE_BUILD_PATH%" %PACKAGE_CMAKE_ARGS%
) else if "%~1"=="--build" (
    set CMD=%CMAKE%
    set ARGS=--build "%CMAKE_BUILD_PATH%"
) else if "%~1"=="--test" (
    pushd "%CMAKE_BUILD_PATH%"
    set CMD=%CTEST%
    if "%CMAKE_BUILD_PATH%"=="" (
        set ARGS=
    ) else (
        set ARGS="%CMAKE_BUILD_PATH%"
    )
) else if "%~1"=="--install" (
    set CMD=%CMAKE%
    set ARGS=--install "%CMAKE_BUILD_PATH%" --prefix "%CMAKE_INSTALL_PREFIX%"
) else if "%~1"=="--pack" (
    pushd "%CMAKE_BUILD_PATH%"
    set CMD=%CPACK%
    set ARGS=-G "%CPACK_GENERATOR%" -B "%CPACK_PACKAGE_DIRECTORY%"
) else goto :help

set ARG_FIRST=1
for %%a in (%*) do (
    if "!ARG_FIRST!"=="1" (
        set ARG_FIRST=0
    ) else (
        set ARGS=!ARGS! %%a
    )
)

echo %CMD% %ARGS%
%CMD% %ARGS%
popd
goto :eof

:help
echo build.cmd mode [arguments]
echo.
echo mode:
echo --generate    start cmake for generating a build system.
echo --build       start cmake for building the targets.
echo --test        start ctest for test targets.
echo --install     start cmake for installing.
echo --pack        start cpack for building a package.
echo.
echo arguments     list of arguments copied verbatum to cmake.
echo.
echo Assumed settings:
echo The first part of this script contains dependencies configuration.
echo Check the configuration before attemting to generate or build.
echo.
echo Examples:
echo This will recreate a build system from scratch.
echo build --generate --fresh
echo.
echo This will build all targets in Debug mode except documentation.
echo build --build --config Release
echo 
echo This will rebuild all targets from scratch in Debug mode except documentaton.
echo build --build --clean-first
echo.
echo This will build only the manual.
echo build --build --target manual
echo.
echo This will build only Doxigen documentation.
echo Entry: %CMAKE_BUILD_PATH%/doxygen/html/index.html.
echo build --build --target docs
echo.
echo This will run all tests, tester must manualy close all window forms.
echo build.sh --test -C Debug
echo.
echo This will run all tests, with output for failing tests.
echo build.sh --test -C Debug --output-on-failure
echo.
goto :eof

