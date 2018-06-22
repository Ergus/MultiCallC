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

#include <libguile.h>
#include "libfun.h"

SCM my_square(SCM x)
{
	return scm_from_int(square(scm_to_int(x)));
}

SCM my_cube(SCM x)
{
	return scm_from_int(cube(scm_to_int(x)));
}

SCM my_print(SCM size, SCM array)
{
	size_t len, inc;
	int csize = scm_to_int(size);
	scm_t_array_handle handle;

	//const double* carray = scm_f64vector_elements(array, &handle, &len, &inc);
	double* carray = scm_f64vector_writable_elements(array, &handle, &len, &inc);

	print(csize, carray);

	scm_array_handle_release(&handle);
}

SCM my_printstr(SCM mystring)
{
	char *cmystring = scm_to_locale_string(mystring);

	printstr(cmystring);

	scm_dynwind_free(cmystring);
}

void init_module()
{
	scm_c_define_gsubr("square", 1, 0, 1, my_square);
	scm_c_define_gsubr("cube", 1, 0, 1, my_cube);
	scm_c_define_gsubr("print", 2, 0, 0, my_print);
	scm_c_define_gsubr("printstr", 1, 0, 0, my_printstr);
}
