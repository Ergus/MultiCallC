cmake_minimum_required (VERSION 3.4)

project (Jimmy CXX Fortran)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/*.cc PROPERTIES COMPILE_FLAGS -fPIC)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(fun SHARED ${PROJECT_SOURCE_DIR}/src/libfun.cc)

# C main.x

add_executable(main_c main.cc)
target_link_libraries(main_c fun)

# FORTRAN main2.x

add_executable(main_f main.f90)
set_target_properties(main_f PROPERTIES LINKER_LANGUAGE Fortran)

target_link_libraries(main_f fun)

# For Python executable

configure_file(${PROJECT_SOURCE_DIR}/main.py ${PROJECT_BINARY_DIR})

# For Ruby executable

configure_file(${PROJECT_SOURCE_DIR}/main.rb ${PROJECT_BINARY_DIR})

# For tests

enable_testing()

add_subdirectory(test)
