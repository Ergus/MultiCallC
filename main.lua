#!/usr/bin/lua

--
-- This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
-- Aguilar Mena.
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, version 3.
--
-- This program is distributed in the hope that it will be useful, but
-- WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
-- General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program. If not, see <http://www.gnu.org/licenses/>.
--

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
