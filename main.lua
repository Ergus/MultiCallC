#!/usr/bin/lua

local my = require "libmodulelua"

-- For formatted printing
printf = function(s,...)
           return io.write(s:format(...))
         end -- function

for i = 0,4 do
   printf("%d\tx^2=%2d\tx^3=%2d\n", i, my.square(i), my.cube(i))
end

size = 6
arr = {}
for i = 1,6 do
   arr[i] = i
end
my.print(size, arr)

mystr = "my string"
my.printstr(mystr)
