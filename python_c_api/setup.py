from distutils.core import setup, Extension

# define the extension module
my_module = Extension('my_module',
                      include_dirs = ['${PROJECT_SOURCE_DIR}/include'],          # -I option
                      sources=['${PROJECT_SOURCE_DIR}/python_c_api/c-module.c'], # source files
                      runtime_library_dirs=['${PROJECT_BINARY_DIR}'],            # rpath
                      library_dirs=['${PROJECT_BINARY_DIR}'],                    # -L option
                      libraries=['fun'])                                         # -l option

# run the setup
setup(ext_modules=[my_module])
