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

* Intergace Go-C with the seudo-package "C" and using header flags. This compiles directly with **go build**

* Interface Go-C without the seudo-package "C" and compiling directly with gccgo.

* Interface Lua-C using the Lua C API and compiling with the intrinsic cmake's FindLua. In the script a custom *printf* is defined to get the exact same output as the other benchmarks.

* Interface Scheme-C (Guile-C) with the Guile C api. There are some small issues with the memory allocation and release.

* Interface Pascal-C (with free pascal compiler). There are some small issues with the printf call from pascal in C.

* Interface Ada-C. I don't know how to print a **\t** in Ada.

* Interface Tcl-C. I use a list instead of a Tcl array because it is the structure that better match C arrays (are indexed and keeps the order.) Because Tcl Arrays are hash tables.

* Interface Ocaml-C. An extra character is required in the printf in the .ml to avoid buffer issues. The example works with the bytecode and the native compiler, but the compile commands are different. There is no way to avoid the extra files in the sources for now. So I added them in the .gitignore.

* Interface Bash-C using bash builtins. This bash functionality is surprisingly undocumented in spite of it is very simple to use. 

* Interface Elisp-C using the emacs module from Emacs-25. This includes the emacs-modules.h header because it is not available in all the systems, even when Emacs supports it. The interface is made barely simple and for real applications the high level wrapper is most recommended for error prevention.

* Interface PHP-C this uses the default php C api, but is compatible only with the php7 C api for simplicity. Code modification shouldn't be complicated to make it backward compatible, but I keep it **as is ** for simplicity. Something really pending is the update in the future of the CMakeLists.txt to search a more general PHP than now.

Author: Jimmy Aguilar Mena
