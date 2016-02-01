#!/usr/bin/env ruby

require 'ffi'

module Libfun
    extend FFI::Library
    ffi_lib './libfun.so'
    attach_function :square, [ :int ], :int
    attach_function :cube, [ :int ], :int
end

for i in 0..4
    printf("%d\tx^2=%2d\tx^3=%2d\n", \
           i,Libfun.square(i),Libfun.cube(i))
end
