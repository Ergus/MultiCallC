#!/usr/bin/env ruby

#
# This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
# Aguilar Mena.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
#

require 'ffi'

module Libfun
    extend FFI::Library
    ffi_lib './libfun.so'
    attach_function :square, [ :int ], :int
    attach_function :cube, [ :int ], :int
    attach_function :print, [ :int, :pointer ], :void
    attach_function :printstr, [ :string ], :void
end

# First Part

for i in 0..4
    printf("%d\tx^2=%2d\tx^3=%2d\n", \
           i,Libfun.square(i),Libfun.cube(i))
end

# Second part

size = 6
array = Array(1..size)                          # Create array [1,2,..6]

pointer = FFI::MemoryPointer.new :double, size  # Create the pointer to the array

pointer.put_array_of_double 0, array            # Fill the memory with your data (ruby array to C)

Libfun.print(size,pointer)

# Get the array and put it in `result_array` for use (C array to Ruby, not used here)
#result_array = result_pointer.read_array_of_double(size)

# Third part
str="my string"

Libfun.printstr(str)
