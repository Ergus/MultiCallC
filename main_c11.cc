/*
 * This file is part of the MultiCallC distribution Copyright (c) 2015 Jimmy
 * Aguilar Mena.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
