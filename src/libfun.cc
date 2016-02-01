
#include <libfun.h>


int square(int x){
    return x*x;
    }

int cube(int x){
    return x*x*x;
    }

void print(int size, double* array){
  for(int i=0;i<size;i++){
    printf("%2.3lf; ",array[i]);
    }
  printf("\n");
  }
