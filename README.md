Simple CMake-CTest Project
=========================

This is a simple project to show in how:

* Create a dynamic library with a source and a header in subdirs.

* Pass integers, double arrays and strings from any language to C.

* Create an executable and link it with the library.

* Create automatic tests for the functions in the library in a subdirectory using assert.

* Interface Python-C with CTypes for the library compiled with CMake.

* Interface Python-C with API for the library compiled with CMake.

* Interface Fortran-C++ with modern Fortran interface and compiled with CMake.

* Interface Ruby-C++ with ffi for the library compiled with CMake.

* Interface Java-C++ with jni for the library compiled with CMake, two new files as wraper src/main_j.cc and include/main_j.h and a test in the CmakeLists.txt because the command is complicated.

* Interfaces C++11 and pure C99 with normal linkage.

* Interface C-C using signals with dl library and without a header.

* Interface NASM-C with array in the stack and direct call. The real challenge is the CMake implementation.

* Interface Julia-C with the native ccall function.

* Interface Rust-C with unsafe and std functions, support for rust manually added in the CMake.

* Intergace Go-C without the seudo-package "C" and compiling directly with gccgo. Maybe sometimes I will add other version.

* Interface Lua-C using the Lua C API and compiling with the intrinsic cmake's FindLua. In the script a custom *printf* is defined to get the exact same output as the other benchmarks..

Author: Jimmy Aguilar Mena
