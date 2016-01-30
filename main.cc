#include "libfun.h"

int main(){
    for(int i=0;i<5;i++){
        printf("%d\tx^2=%2d\tx^3=%2d\n", i, square(i), cube(i));
        }
    
    return 0;
    }
