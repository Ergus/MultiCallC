#include "libfun.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <list>
#include <numeric>


using namespace std;

int main(){
    // First test

    list<int> l(5);
    iota(l.begin(),l.end(),0);

    for(auto i : l){
        cout<<i<<"\tx^2="<<setw(2)<<square(i)<<"\tx^3="<<setw(2)<<cube(i)<<endl;
        }

    // Secound test, pass array
    const auto size=6;
    vector<double> arr(size);
    
    int n = {0};
    generate(arr.begin(), arr.end(), [&n]{ return (double)++n;});  //the same than iota
    print(size,&arr[0]);

    // Third test
    string str="my string";
    printstr(str.c_str());
    
    return 0;
    }
