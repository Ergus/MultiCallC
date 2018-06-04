cmake_minimum_required (VERSION 3.4)

project (Jimmy C CXX Fortran)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/*.cc PROPERTIES COMPILE_FLAGS -fPIC)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Build C library ################################

add_library(fun SHARED ${PROJECT_SOURCE_DIR}/src/libfun.cc)

# Nasm ###########################################

find_program(NASM "nasm")

IF(NASM)
  message(STATUS "NASM compiler found: " ${NASM})
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
ELSE(NASM)
  message(WARNING "NASM compiler NOT found: " ${NASM})
ENDIF(NASM)

# C main_c #######################################

add_executable(main_c main.c)
target_link_libraries(main_c fun)

add_test(NAME Test_C COMMAND main_c)

# C++ 11 main_c11 ################################
# Both next lines work to enable c++11
#ADD_COMPILE_OPTIONS(-std=c++11)  
#set_source_files_properties(main_c11.cc PROPERTIES COMPILE_FLAGS -std=c++11)

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

FIND_PATH(JAVA_HOME
  jre/bin/java
  HINTS /usr/lib/jvm/java-8-openjdk /usr/lib/jvm/java-8-openjdk-amd64 /usr/lib/jvm/default
  NO_DEFAULT_PATH
  )

if(NOT JAVA_HOME STREQUAL "JAVA_HOME-NOTFOUND")
  include(UseJava)
  find_package(Java MODULE)
  find_package(JNI MODULE)

  if(Java_FOUND AND JNI_FOUND)
    set(jversion ${Java_VERSION_MAJOR}.${Java_VERSION_MINOR})

    set(CMAKE_JAVA_COMPILE_FLAGS "-source" ${jversion} "-target" ${jversion})

    include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} ${PROJECT_SOURCE_DIR}/include)

    add_library(funjava MODULE ${PROJECT_SOURCE_DIR}/src/main_j.cc)

    target_link_libraries(funjava fun ${JNI_LIBRARIES})

    add_jar(main_j main_j.java)
    
    get_target_property(_jarFile main_j JAR_FILE)

    add_test(NAME Test_Java
      COMMAND ${Java_JAVA_EXECUTABLE}
      -Djava.library.path=${CMAKE_CURRENT_BINARY_DIR}
      -cp ${_jarFile} main_j)
    
  endif(Java_FOUND AND JNI_FOUND)
  
else()
  message(STATUS "JAVA_HOME=" ${JAVA_HOME})
endif()



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
   include_directories(${PYTHON_INCLUDE_DIRS})

   add_library(mymodule MODULE ${PROJECT_SOURCE_DIR}/src/c-module.c) 
   set_target_properties(mymodule PROPERTIES PREFIX "")
   target_link_libraries(mymodule fun ${PYTHON_LIBRARIES})

   configure_file(${PROJECT_SOURCE_DIR}/main_CAPI.py ${PROJECT_BINARY_DIR})
   add_test(NAME Test_Python_C_API COMMAND main_CAPI.py)
   
ENDIF(PYTHONLIBS_FOUND)

# For Julia executable ###########################

configure_file(${PROJECT_SOURCE_DIR}/main.jl ${PROJECT_BINARY_DIR})

add_test(NAME Test_Julia COMMAND main.jl)

# For Ruby executable ############################

configure_file(${PROJECT_SOURCE_DIR}/main.rb ${PROJECT_BINARY_DIR})

add_test(NAME Test_Ruby COMMAND main.rb)

# Rust ###########################################

function(buildrs input output)
  set(SOURCE_RS "${PROJECT_SOURCE_DIR}/${input}")
  set(EXECUT_RS "${output}")

  add_custom_command(OUTPUT ${EXECUT_RS}
    COMMAND ${RUSTC} -C link-args=-Wl,-rpath,${PROJECT_BINARY_DIR} -L${PROJECT_BINARY_DIR} -lfun ${SOURCE_RS} -o ${EXECUT_RS}
    DEPENDS fun "${PROJECT_SOURCE_DIR}/main.rs"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

  add_custom_target("${output}_rs" ALL
    DEPENDS ${EXECUT_RS}
    )
endfunction()

find_program(RUSTC "rustc")

if (RUSTC)
  buildrs(main.rs main_rs)
  add_test(NAME Test_Rust COMMAND main_rs)
endif()

# Go #############################################

find_program(GCCGO "gccgo")

function(buildgo input output)
  set(SOURCE_GO "${PROJECT_SOURCE_DIR}/${input}")
  set(EXECUT_GO "${output}")

  add_custom_command(OUTPUT ${EXECUT_GO}
    COMMAND ${GCCGO} ${SOURCE_GO} -o ${EXECUT_GO} -L${PROJECT_BINARY_DIR} -lfun -Wl,-rpath,${PROJECT_BINARY_DIR}
    DEPENDS fun "${PROJECT_SOURCE_DIR}/main.go"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
  
  add_custom_target("${output}_go" ALL
    DEPENDS ${EXECUT_GO}
    )

endfunction()

if(GCCGO)
  buildgo(main.go main_go)
  add_test(NAME Test_Go COMMAND main_go)
endif()
  
# For tests ######################################

enable_testing()
add_subdirectory(test)

