
find_program(PYTHON "python")

if (PYTHON)
  set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
  set(SETUP_PY "${PROJECT_BINARY_DIR}/setup.py")

  configure_file(${SETUP_PY_IN} ${SETUP_PY})

  add_custom_target(
    mymodule.so ALL
    COMMAND ${PYTHON} setup.py build_ext --inplace
    DEPENDS ${PROJECT_BINARY_DIR}/libfun.so
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
  
#  install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")

endif()
