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
    void printstr(const char *);
    
#ifdef __cplusplus
}
#endif

#endif
