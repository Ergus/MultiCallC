#include "libfun.h"
#include <assert.h>

int main(){
    for(int i=0;i<5;i++){
        assert(cube(i)==i*i*i);
        }
    
    return 0;
    }
