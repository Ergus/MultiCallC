#!/usr/bin/env ruby

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
