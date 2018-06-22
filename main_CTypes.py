#!/usr/bin/env python3

#
# This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
# Aguilar Mena.
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

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
libfun.print.restype= None
libfun.print.argtypes=[C.c_int,
                      np.ctypeslib.ndpointer(C.c_double, flags="C_CONTIGUOUS")]

size=6
arr= np.arange(1,size+1,dtype=C.c_double)
libfun.print(size,arr)

# Third test
libfun.printstr.restype= None
libfun.printstr.argtypes=[C.c_char_p]

str="my string"

libfun.printstr(str.encode('utf-8'))



