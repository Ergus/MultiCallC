#include <dlfcn.h>
#include <stdio.h>

int main(){
    void *libfun;
    int (*square)(int);
    int (*cube)(int);
    void (*print)(int, double*);
    
    libfun = dlopen("./libfun.so",RTLD_LAZY);

    if(libfun){
        square = (int (*)(int)) dlsym(libfun,"square");
        cube = (int (*)(int)) dlsym(libfun,"cube");
        print = (void (*)(int, double*)) dlsym(libfun,"print");
        }
    else{
        printf("Error Opening plugging\n");
        return -1;
        }
    
    // First test
    for(int i=0;i<5;i++){
        printf("%d\tx^2=%2d\tx^3=%2d\n", i, (*square)(i), (*cube)(i));
        }
    
    //Secound test, pass array
    const int size=6;
    double arr[size];
    
    for(int i=0;i<size;i++) arr[i]=double(i+1);
    
    (*print)(size,arr);

    dlclose(libfun);
    
    return 0;
    }
