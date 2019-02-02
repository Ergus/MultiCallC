#!/usr/bin/julia

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

import Printf
# First part
for i = 0:4
    square = ccall( (:square,"./libfun"), Cint, (Cint,), i )
    cube   = ccall( (:cube,  "./libfun"), Int64, (Int64,), i ) #same than above
    Printf.@printf("%d\tx^2=%2d\tx^3=%2d\n",i,square,cube)
end

# Second part
size=6
arr=collect(1.: 6)
ccall( (:print, "./libfun"), Cvoid, (Cint, Ptr{Cdouble}), size, arr )

# Third part
mystring="my string"

ccall( (:printstr, "./libfun"), Cvoid, (Cstring,), mystring)

