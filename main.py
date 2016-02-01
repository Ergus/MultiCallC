#!/usr/bin/env python

import ctypes as C
import numpy as np

libfun = C.CDLL("./libfun.so")

# First test
libfun.square.restype=C.c_int
libfun.square.argtypes=[C.c_int]

libfun.cube.restype=C.c_int
libfun.cube.argtypes=[C.c_int]

for i in range(5):
    print("%d\tx^2=%2d\tx^3=%2d" %  \
          (i, libfun.square(i), libfun.cube(i)));

# Second test
libfun.print.argtypes=[C.c_int,
                      np.ctypeslib.ndpointer(C.c_double, flags="C_CONTIGUOUS")]

size=6
arr= np.arange(1,size+1,dtype=C.c_double)

libfun.print(size,arr)


