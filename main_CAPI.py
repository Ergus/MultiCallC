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

import modulepython as my

for i in range(5):
    print("%d\tx^2=%2d\tx^3=%2d" %  \
          (i, my.square(i), my.cube(i)))

size = 6
arr = range(1, size+1)
my.print(size, arr)

mystr = "my string"
my.printstr(mystr)
