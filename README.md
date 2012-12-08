C Data Structures Lib
==============================================

    Version:    0.1
    Created By: Michael D. Lowis
    Email:      mike@mdlowis.com

About This Project
----------------------------------------------
This library is meant to be a collection of common data structures, implemented
in C, that can be used in any C or C++ program. The goal is to implement many
of the same data structures that the C++ STL provides, in pure C.

License
----------------------------------------------
Unless explicitly stated otherwise, all code and documentation contained within
this repository is released under the BSD 2-Clause license. The text for this
license can be found in the LICENSE.md file.

Requirements For Building
----------------------------------------------
The only external dependencies currently required to build this library are
Premake 4 and a toolchain that is supported by Premake.

Build Instructions
----------------------------------------------
This project uses Premake 4 in order to generate cross-platform build scripts.
The first step in building the library is to generate the build scripts for
your system. Premake supports a variety of different build environments and you
will need to select the target that you wish to use. To list the available
targets simply run the following command:

    premake4 --help

You should then be presented with a list of options for premake with a section
at the end that looks like this:

    ACTIONS

     clean             Remove all binaries and generated files
     codeblocks        Generate Code::Blocks project files
     codelite          Generate CodeLite project files
     gmake             Generate GNU makefiles for POSIX, MinGW, and Cygwin
     vs2002            Generate Microsoft Visual Studio 2002 project files
     vs2003            Generate Microsoft Visual Studio 2003 project files
     vs2005            Generate Microsoft Visual Studio 2005 project files
     vs2008            Generate Microsoft Visual Studio 2008 project files
     vs2010            Generate Visual Studio 2010 project files (experimental)
     xcode3            Generate Apple Xcode 3 project files (experimental)

This is the list of build script targets that are supported. To generate build
scripts to use with GNU Make for instantce, you could choose the gmake target
by using the following command:

    premake4 gmake

Once the Make scripts are generated you can build the project and run all unit
tests with the following command:

    make

You can build just the with the following command:

    make cds

You can build and execute just the unit tests with the following command:

    make tests

Project Files and Directories
----------------------------------------------

    build/         This is the directory where all output files will be placed.
    source/        The source for the project.
    tests/         Unit test and mock files.
    tools/         Tools required by the build system.
    Doxyfile       Doxygen documentation generator configuration.
    LICENSE.md     The software license notification.
    premake4.lua   A premake4 configuration file for generating build scripts.
    project.vim    A VIM script with project specific configurations.
    README.md      You're reading this file right now!

