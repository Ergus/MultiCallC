cmake_minimum_required (VERSION 3.4)

project (main)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/*.cc PROPERTIES COMPILE_FLAGS -fPIC)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(fun SHARED ${PROJECT_SOURCE_DIR}/src/libfun.cc)

add_executable(main main.cc)

target_link_libraries(main fun)

# For tests

enable_testing()

add_subdirectory(test)

# For Python executable

configure_file(${PROJECT_SOURCE_DIR}/main.py ${PROJECT_BINARY_DIR})
