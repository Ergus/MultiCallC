Simple CMake-CTest Project
=========================

This is a simple project to show in how:

* Create a dynamic library with a source and a header in subdirs.

* Pass integers and a double array from any language to C.

* Create an executable and link it with the library.

* Create automatic tests for the functions in the library in a subdirectory using assert.

* Interface Python-C++ with CTypes for the library compiled with CMake.

* Interface Fortran-C++ with modern Fortran interface and compiled with CMake.

* Interface Ruby-C++ with ffi for the library compiled with CMake.

* Interface Java-C++ with jni for the library compiled with CMake, two new files as wraper src/main_j.cc and include/main_j.h and a test in the CmakeLists.txt because the command is complicated.

* Interface C-C using signals with dl library and without a header.

* Interface NASM-C with array in the stack and direct call. The real challenge is the CMake implementation.

Author: Jimmy Aguilar Mena
