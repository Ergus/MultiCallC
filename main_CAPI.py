#!/usr/bin/env python3

import mymodule as my

for i in range(5):
    print("%d\tx^2=%2d\tx^3=%2d" %  \
          (i, my.square(i), my.cube(i)));
    
size=6
arr= range(1,size+1)
my.print(size,arr)

str="my string"
my.printstr(str)
