#!/usr/bin/env ruby

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

require './moduleruby'

# First Part
for i in 0..4
  printf("%d\tx^2=%2d\tx^3=%2d\n",
         i, ModuleRuby.square(i), ModuleRuby.cube(i))
end

# Second part
size = 6
array = Array(1..size)                          # Create array [1,2,..6]

ModuleRuby.print(size, array)

# Third part
str="my string"
ModuleRuby.printstr(str)
