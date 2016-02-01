#!/usr/bin/env python

import ctypes as C
import numpy as np

libfun = C.CDLL("./libfun.so")

libfun.square.restype=C.c_int
libfun.square.argtypes=[C.c_int]

libfun.cube.restype=C.c_int
libfun.cube.argtypes=[C.c_int]

for i in range(5):
    print("%d\tx^2=%2d\tx^3=%2d" %  \
          (i, libfun.square(i), libfun.cube(i)));
