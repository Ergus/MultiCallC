#
# This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
# Aguilar Mena.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required (VERSION 3.4)

project(CMake-CTest
        VERSION 1.0
        LANGUAGES C CXX Fortran)

project (Jimmy C CXX Fortran)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/*.cc PROPERTIES COMPILE_FLAGS -fPIC)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Build C library ################################

add_library(fun SHARED ${PROJECT_SOURCE_DIR}/src/libfun.cc)

# Nasm ###########################################

find_program(NASM "nasm")

IF (NASM)
  message(STATUS "Found NASM compiler: ${NASM}")
  set(CMAKE_C_SIZEOF_DATA_PTR 8)
  set(ASM_DIALECT "_NASM")

  enable_language(ASM_NASM)

  set(CMAKE_ASM_NASM_COMPILER ${NASM})
  set(CMAKE_ASM_NASM_LINKER "gcc")


  set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")
  set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${CMAKE_ASM_NASM_LINKER} <OBJECTS> -o <TARGET> <LINK_LIBRARIES> -Wl,-rpath,<CMAKE_CURRENT_BINARY_DIR>")

  add_executable(main_asm main.asm)
  target_link_libraries(main_asm fun)

  add_test(NAME Test_NASM COMMAND main_asm)
ELSE (NASM)
  message(WARNING "NASM compiler NOT found: " ${NASM})
ENDIF (NASM)

# C main_c #######################################

add_executable(main_c main.c)
target_link_libraries(main_c fun)

add_test(NAME Test_C COMMAND main_c)

# C++ 11 main_c11 ################################
# Both next lines work to enable c++11

add_executable(main_c11 main_c11.cc)
target_compile_features(main_c11 PRIVATE cxx_constexpr)  # This finds the options and sets -std=c++11 if needed

target_link_libraries(main_c11 fun)

add_test(NAME Test_C++11 COMMAND main_c)

# C main with signals using dynamic linking ######

add_executable(main_S main_S.cc)
target_link_libraries(main_S dl)

add_test(NAME Test_Signal COMMAND main_S)

# FORTRAN main_f #################################

add_executable(main_f main.f90)
set_target_properties(main_f PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(main_f fun)

add_test(NAME Test_Fortran COMMAND main_f)

# Java main_j ####################################

include(UseJava)
find_package(Java MODULE)
find_package(JNI MODULE)

if (Java_FOUND AND JNI_FOUND)
  set(jversion ${Java_VERSION_MAJOR}.${Java_VERSION_MINOR})

  set(CMAKE_JAVA_COMPILE_FLAGS "-source" ${jversion} "-target" ${jversion})

  add_library(modulejava MODULE ${PROJECT_SOURCE_DIR}/src/c-java.cc)

  target_include_directories(modulejava PRIVATE ${JAVA_INCLUDE_PATH}
		${JAVA_INCLUDE_PATH2} ${PROJECT_SOURCE_DIR}/include)

  target_link_libraries(modulejava fun ${JNI_LIBRARIES})

  add_jar(main_j main_j.java)

  get_target_property(_jarFile main_j JAR_FILE)

  add_test(NAME Test_Java
    COMMAND ${Java_JAVA_EXECUTABLE}
    -Djava.library.path=${CMAKE_CURRENT_BINARY_DIR}
    -cp ${_jarFile} main_j)
else (Java_FOUND AND JNI_FOUND)
  message("Java not found")
endif (Java_FOUND AND JNI_FOUND)

# For Python executable using CTypes #############

set(Python_ADDITIONAL_VERSIONS 3.7 3.6 3.5 3.4 3.3 3.2 3.1)
FIND_PACKAGE(PythonInterp MODULE)

IF(PYTHONINTERP_FOUND)
  configure_file(${PROJECT_SOURCE_DIR}/main_CTypes.py ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Python_CTypes COMMAND main_CTypes.py)
ENDIF(PYTHONINTERP_FOUND)

# For python2 using the wrapper in C side ########

find_package(PythonLibs MODULE)

IF(PYTHONLIBS_FOUND)
  add_library(modulepython MODULE ${PROJECT_SOURCE_DIR}/src/c-python.c)
  set_target_properties(modulepython PROPERTIES PREFIX "")
  target_link_libraries(modulepython fun ${PYTHON_LIBRARIES})
  target_include_directories(modulepython PRIVATE ${PYTHON_INCLUDE_DIRS})

  configure_file(${PROJECT_SOURCE_DIR}/main_CAPI.py ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Python_C_API COMMAND main_CAPI.py)
ENDIF(PYTHONLIBS_FOUND)

# For Julia executable ###########################

find_program(JULIA_EXECUTABLE julia)

if (JULIA_EXECUTABLE)
  configure_file(${PROJECT_SOURCE_DIR}/main.jl ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Julia COMMAND ${JULIA_EXECUTABLE} main.jl)
else(JULIA_EXECUTABLE)
  message(STATUS "Julia executable not found!!")
endif (JULIA_EXECUTABLE)

# For Ruby executable ############################

find_package(Ruby MODULE)

if (RUBY_FOUND)
  configure_file(${PROJECT_SOURCE_DIR}/main_ffi.rb ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Ruby_ffi COMMAND ${RUBY_EXECUTABLE} main_ffi.rb)

  add_library(moduleruby MODULE ${PROJECT_SOURCE_DIR}/src/c-ruby.c)
  target_include_directories(moduleruby PRIVATE ${RUBY_INCLUDE_DIRS})
  set_target_properties(moduleruby PROPERTIES PREFIX "")
  target_link_libraries(moduleruby fun ${RUBY_LIBRARIES})
  configure_file(${PROJECT_SOURCE_DIR}/main_CAPI.rb ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Ruby_C_API COMMAND ${RUBY_EXECUTABLE} main_CAPI.rb)
endif (RUBY_FOUND)

# Rust ###########################################

find_program(RUSTC_COMPILER rustc)

if (RUSTC_COMPILER)
  message(STATUS "Found Rust compiler: ${RUSTC_COMPILER}")
  function(buildrs input output)
	set(SOURCE_RS "${PROJECT_SOURCE_DIR}/${input}")

	add_custom_command(OUTPUT ${output}
      COMMAND ${RUSTC_COMPILER} -C link-args=-Wl,-rpath,${PROJECT_BINARY_DIR} -L${PROJECT_BINARY_DIR} -lfun ${SOURCE_RS} -o ${output}
      DEPENDS fun "${PROJECT_SOURCE_DIR}/main.rs"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      )

	add_custom_target("${output}_rs" ALL DEPENDS ${output})
  endfunction()

  buildrs(main.rs main_rs)
  add_test(NAME Test_Rust COMMAND main_rs)
else (RUSTC_COMPILER)
  message(STATUS "Rust compiler not found")
endif (RUSTC_COMPILER)

# Go #############################################

find_program(GCCGO_COMPILER gccgo)

if (GCCGO_COMPILER)
  message(STATUS "Found GCCGO compiler: ${GCCGO_COMPILER}")

  function (buildgo input output)
	set(SOURCE_GO "${PROJECT_SOURCE_DIR}/${input}")

	add_custom_command(OUTPUT ${output}
      COMMAND ${GCCGO_COMPILER} ${SOURCE_GO} -o ${output} -L${PROJECT_BINARY_DIR} -lfun -Wl,-rpath,${PROJECT_BINARY_DIR}
      DEPENDS fun "${PROJECT_SOURCE_DIR}/main.go"
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      )

	add_custom_target("${output}_go" ALL DEPENDS ${output})
  endfunction ()

  buildgo(main.go main_go)
  add_test(NAME Test_Go COMMAND main_go)

else (GCCGO_COMPILER)
  message(STATUS "GCCGO compiler not found")
endif (GCCGO_COMPILER)

# Lua ############################################

find_package(Lua MODULE)

if (LUA_FOUND)
  add_library(modulelua SHARED ${PROJECT_SOURCE_DIR}/src/c-lua.c)
  target_include_directories(modulelua PRIVATE ${LUA_INCLUDE_DIR})
  target_link_libraries(modulelua fun ${LUA_LIBRARIES})

  configure_file(${PROJECT_SOURCE_DIR}/main.lua ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Lua COMMAND main.lua)
endif (LUA_FOUND)

# Scheme-guile ###################################

find_program(GUILE guile)
find_path(GUILE_INCLUDE_DIR libguile.h PATH_SUFFIXES guile guile/2.2)
find_library(LIBGUILE libguile-2.2.so)

if (GUILE AND LIBGUILE AND GUILE_INCLUDE_DIR)
  message(STATUS "Found Guile: ${GUILE}")

  add_library(modulescheme SHARED ${PROJECT_SOURCE_DIR}/src/c-scheme.c)
  target_include_directories(modulescheme PRIVATE ${GUILE_INCLUDE_DIR})
  target_link_libraries(modulescheme fun ${LIBGUILE})

  configure_file(${PROJECT_SOURCE_DIR}/main.scm ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Guile COMMAND main.scm)
else ()
  message(STATUS "Guile not found: guile=${GUILE} libguile=${LIBGUILE}")
endif()

# Pascal #########################################

find_program(FPC_COMPILER fpc)

if (FPC_COMPILER)
  message(STATUS "Found FPC compiler: ${FPC_COMPILER}")

  function (buildfpc input output)
	set(SOURCE_FPC "${PROJECT_SOURCE_DIR}/${input}")

	add_custom_command(OUTPUT ${output}
      COMMAND ${FPC_COMPILER} ${SOURCE_FPC} -Fl${PROJECT_BINARY_DIR}
										  -FE${PROJECT_BINARY_DIR}
										  -k-rpath
										  -k${PROJECT_BINARY_DIR}
										  -o${output}
      DEPENDS fun ${SOURCE_FPC}
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      )

	add_custom_target("${output}_pas" ALL DEPENDS ${output})
  endfunction ()

  buildfpc(main.pas main_pascal)
  add_test(NAME Test_Pascal COMMAND main_pascal)
else (FPC_COMPILER)
  message(STATUS "Pascal compiler fpc not found")
endif (FPC_COMPILER)

# Ada ###########################################

find_program(GNAT_BIND gnatbind)
find_program(GNAT_LINK gnatlink)

if (GNAT_BIND AND GNAT_LINK)
  message(STATUS "Found ADA: ${GNAT_BIND} and ${GNAT_BIND}")

  function (buildada input output)
	set(SOURCE_ADA "${PROJECT_SOURCE_DIR}/${input}")
	set(ALI "${output}.ali")

	add_custom_command(OUTPUT ${output}
      COMMAND gcc -c ${SOURCE_ADA}
	  COMMAND ${GNAT_BIND} -x ${ALI}
	  COMMAND ${GNAT_LINK} ${ALI} -o ${output} --LINK=gcc -L${PROJECT_BINARY_DIR} -lfun -Wl,-rpath,${PROJECT_BINARY_DIR}
      DEPENDS fun ${SOURCE_ADA}
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      )

	add_custom_target("${output}_ada" ALL DEPENDS ${output})
  endfunction ()

  buildada(main_ada.adb main_ada)
  add_test(NAME Test_Ada COMMAND main_ada)

else ()
  message(STATUS "GNATLINK and GNATBIND not found")
endif()

# Tcl ############################################

find_path(TCL_INCLUDE_DIR tcl.h)
find_library(LIBTCL libtcl.so)

if (TCL_INCLUDE_DIR AND LIBTCL)
  message(STATUS "Found header and libraries in: ${TCL_INCLUDE_DIR} and ${LIBTCL}")

  add_library(moduletcl SHARED ${PROJECT_SOURCE_DIR}/src/c-tcl.c)
  target_include_directories(moduletcl PRIVATE ${TCL_INCLUDE_DIR})
  set_target_properties(moduletcl PROPERTIES PREFIX "")
  target_link_libraries(moduletcl fun ${LIBTCL})

  configure_file(${PROJECT_SOURCE_DIR}/main.tcl ${PROJECT_BINARY_DIR})
  add_test(NAME Test_Tcl COMMAND main.tcl)
else ()
  message(STATUS "tcl library or header not found")
endif ()

# Ocaml ##########################################

find_program(OCAMLC ocamlopt)

if (OCAMLC)
  message(STATUS "Found ocaml compiler: ${OCAMLC}")

  execute_process(COMMAND ${OCAMLC} -where
	OUTPUT_VARIABLE OCAML_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  add_library(moduleocaml SHARED ${PROJECT_SOURCE_DIR}/src/c-ocaml.c)
  target_include_directories(moduleocaml PRIVATE ${OCAML_INCLUDE_DIR})
  target_link_libraries(moduleocaml fun)

  function (buildocaml input output)
	set(SOURCE_OCAML "${PROJECT_SOURCE_DIR}/${input}")

	add_custom_command(OUTPUT ${output}
	  #COMMAND ${OCAMLC} ${SOURCE_OCAML} -dllpath ${PROJECT_BINARY_DIR} -dllib libmoduleocaml -o ${output} -I ${PROJECT_BINARY_DIR}
	  COMMAND ${OCAMLC} ${SOURCE_OCAML} -cclib "-L${PROJECT_BINARY_DIR} -lmoduleocaml -Wl,-rpath,${PROJECT_BINARY_DIR}" -o ${output} -I ${PROJECT_BINARY_DIR}
      DEPENDS fun ${SOURCE_OCAML} moduleocaml
      WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
      )

	add_custom_target("${output}_ocaml" ALL DEPENDS ${output})
  endfunction ()

  buildocaml(main.ml main_ocaml)
  add_test(NAME Test_ocaml COMMAND main_ocaml)

else ()
  message(STATUS "ocaml compiler or header not found")
endif ()

# Bash ###########################################

find_path(BASH_INCLUDE_DIR builtins.h PATH_SUFFIXES bash)

if (BASH_INCLUDE_DIR)
  message(STATUS "Found bash headers: ${BASH_INCLUDE_DIR}")

  set(BASH_INCLUDES ${BASH_INCLUDE_DIR} ${BASH_INCLUDE_DIR}/builtins ${BASH_INCLUDE_DIR}/include)

  add_library(modulebash SHARED ${PROJECT_SOURCE_DIR}/src/c-bash.c)
  target_include_directories(modulebash PRIVATE ${BASH_INCLUDES})
  #set_target_properties(modulebash PROPERTIES PREFIX "")
  target_link_libraries(modulebash fun)

  configure_file(${PROJECT_SOURCE_DIR}/main.sh ${PROJECT_BINARY_DIR} COPYONLY)
  add_test(NAME Test_Bash COMMAND main.sh)

else ()
  message(STATUS "no bash headers found")
endif()

# For tests ######################################
enable_testing()
add_subdirectory(test)

