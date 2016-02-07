#include "libfun.h"

int main(){

    int i;
    
    // First test
    for(i=0;i<5;i++){
        printf("%d\tx^2=%2d\tx^3=%2d\n", i, square(i), cube(i));
        }

    // Secound test, pass array
    const int size=6;
    double arr[size];
    
    for(i=0;i<size;i++) arr[i]=(double)(i+1);
    
    print(size,arr);

    // Third test
    char str[]="my string";
    printstr(str);
    
    return 0;
    }
