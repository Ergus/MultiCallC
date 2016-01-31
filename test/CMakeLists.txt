
enable_testing()

# C tests

add_executable(test1.x test1.cc)
target_link_libraries(test1.x fun)
add_test(test1 test1.x)


add_executable(test2.x test2.cc)
target_link_libraries(test2.x fun)
add_test(my_test2 test2.x)

# Fortran test

add_executable(test3.x test3.f90)
set_target_properties(test3.x PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(test3.x fun)
add_test(test_fortran test3.x)


