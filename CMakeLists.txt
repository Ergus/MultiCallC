cmake_minimum_required (VERSION 3.4)

project (Jimmy CXX Fortran)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
set_source_files_properties(${PROJECT_SOURCE_DIR}/src/*.cc PROPERTIES COMPILE_FLAGS -fPIC)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_library(fun SHARED ${PROJECT_SOURCE_DIR}/src/libfun.cc)

# C main_c

add_executable(main_c main.cc)
target_link_libraries(main_c fun)

# FORTRAN main_f

add_executable(main_f main.f90)
set_target_properties(main_f PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(main_f fun)

# Java main_j
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

add_test(NAME Test_main_j
  COMMAND ${Java_JAVA_EXECUTABLE}
  -Djava.library.path=${CMAKE_CURRENT_BINARY_DIR}
  -cp ${_jarFile} main_j)


# For Python executable

configure_file(${PROJECT_SOURCE_DIR}/main.py ${PROJECT_BINARY_DIR})

# For Ruby executable

configure_file(${PROJECT_SOURCE_DIR}/main.rb ${PROJECT_BINARY_DIR})

# For tests

enable_testing()

add_subdirectory(test)
