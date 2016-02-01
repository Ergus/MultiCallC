
#ifndef LIBFUN_H
#define LIBFUN_H

#include <stdio.h>
#include <stdlib.h>

// The macro and the extern is to make the code
// compatible with CTypes
#ifdef __cplusplus
extern "C" {
#endif
    
    int square(int);
    int cube(int);
    void print(int, double*);
    
#ifdef __cplusplus
}
#endif

#endif
