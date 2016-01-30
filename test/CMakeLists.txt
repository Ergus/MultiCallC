enable_testing()

add_executable(test1.x test1.cc)

target_link_libraries(test1.x fun)

add_test(test1 test1.x)
