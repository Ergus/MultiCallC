cmake_minimum_required (VERSION 3.4)

project (main)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(fun STATIC ${PROJECT_SOURCE_DIR}/src/libfun.cc)

add_executable(main main.cc)

target_link_libraries(main fun)


enable_testing()
