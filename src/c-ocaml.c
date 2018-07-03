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

#include <stdio.h>
#include <assert.h>
#include <caml/mlvalues.h>

#include "libfun.h"

CAMLprim value my_square(value v)
{
    int i = Int_val(v);
    return Val_int(square(i));
}

CAMLprim value my_cube(value v)
{
    int i = Int_val(v);
    return Val_int(cube(i));
}

CAMLprim value my_print(value size, value array)
{
	int csize = Int_val(size);
	int osize = Wosize_val(array);

	assert(csize == osize);

	double *arr = malloc(csize*sizeof(double));

	for (int i = 0; i < csize; ++i)
		arr[i] = Double_field(array, i);

	print(csize, arr);

	free(arr);
	return Val_unit;
}

CAMLprim value my_printstr(value str)
{

	char *cstr = String_val(str);

	printstr(cstr);

	return Val_unit;
}

