cmake_minimum_required (VERSION 3.4)

project (Jimmy C CXX Fortran)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/*.cc PROPERTIES COMPILE_FLAGS -fPIC)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Build C library ################################

add_library(fun SHARED ${PROJECT_SOURCE_DIR}/src/libfun.cc)

# Nasm ###########################################

set(CMAKE_C_SIZEOF_DATA_PTR 8)
enable_language(ASM_NASM)

set(CMAKE_ASM_NASM_COMPILER "nasm")
set(CMAKE_ASM_NASM_LINKER "gcc")

set(ASM_DIALECT "_NASM")

set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "${CMAKE_ASM_NASM_LINKER} <OBJECTS> -o <TARGET> <LINK_LIBRARIES> -Wl,-rpath,<CMAKE_CURRENT_BINARY_DIR>")


add_executable(main_asm main.asm)
target_link_libraries(main_asm fun)

add_test(NAME Test_NASM COMMAND main_asm)

# C main_c #######################################

add_executable(main_c main.c)
target_link_libraries(main_c fun)

add_test(NAME Test_C COMMAND main_c)

# C++ 11 main_c11 ################################

set_source_files_properties(main_c11.cc PROPERTIES COMPILE_FLAGS -std=c++11)

add_executable(main_c11 main_c11.cc)
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

set(JAVA_HOME "/usr/lib/jvm/java-8-openjdk")

find_package(Java REQUIRED)
include(UseJava)

find_package(JNI)

set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")

include_directories(${JAVA_INCLUDE_PATH} ${JAVA_INCLUDE_PATH2} ${PROJECT_SOURCE_DIR}/include)

add_library(funjava MODULE ${PROJECT_SOURCE_DIR}/src/main_j.cc)

target_link_libraries(funjava ${JNI_LIBRARIES})
target_link_libraries(funjava fun)

add_jar(main_j main_j.java)

get_target_property(_jarFile main_j JAR_FILE)
get_target_property(_classDir main_j CLASSDIR)

add_test(NAME Test_Java
  COMMAND ${Java_JAVA_EXECUTABLE}
  -Djava.library.path=${CMAKE_CURRENT_BINARY_DIR}
  -cp ${_jarFile} main_j)

# For Python executable using CTypes #############

configure_file(${PROJECT_SOURCE_DIR}/main_CTypes.py ${PROJECT_BINARY_DIR})

add_test(NAME Test_Python_CTypes COMMAND main_CTypes.py)

# For python2 using the wrapper in C side ########

add_subdirectory(python_c_api)
configure_file(${PROJECT_SOURCE_DIR}/main_CAPI.py ${PROJECT_BINARY_DIR})

add_test(NAME Test_Python_C_API COMMAND main_CAPI.py)

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
    DEPENDS ${PROJECT_BINARY_DIR}/libfun.so "${PROJECT_SOURCE_DIR}/main.rs"
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
    COMMAND ${GCCGO} ${SOURCE_GO} -L${PROJECT_BINARY_DIR} -lfun -o ${EXECUT_GO} -Wl,-rpath,${PROJECT_BINARY_DIR}
    DEPENDS ${PROJECT_BINARY_DIR}/libfun.so "${PROJECT_SOURCE_DIR}/main.go"
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

