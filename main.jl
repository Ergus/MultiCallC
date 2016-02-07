#!/usr/bin/julia

# First part
for i = 0:4
    square = ccall( (:square,"./libfun"), Cint, (Cint,), i )
    cube   = ccall( (:cube,  "./libfun"), Int64, (Int64,), i ) #same than above
    @printf("%d\tx^2=%2d\tx^3=%2d\n",i,square,cube)
end

# Second part
size=6
arr=collect(1.: 6)
ccall( (:print, "./libfun"), Void, (Cint, Ptr{Cdouble}), size, arr )

# Third part
mystring="my string"

ccall( (:printstr, "./libfun"), Void, (Cstring,), mystring)

