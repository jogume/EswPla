@echo off
REM ****************************************************************************
REM  \copyright       EswPla FreeRTOS Project
REM  \file            build.bat
REM  \brief           Build script that sets BUILDROOT and compiler PATH
REM ****************************************************************************

REM Set BUILDROOT environment variable for compiler location (use forward slashes)
set BUILDROOT=C:/build_tools

REM Set compiler bin directory in PATH for MSYS2 GCC DLL dependencies
REM Uses T_gcc_mingw~V15.2.0/ucrt64/bin structure (MSYS2 installation)
set PATH=C:\build_tools\T_gcc_mingw~V15.2.0\ucrt64\bin;C:\build_tools\T_gcc_mingw~V15.2.0\usr\bin;%PATH%

REM Forward all arguments to make
make %*
