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

#include "ruby.h"
#include "../include/libfun.h"

static VALUE mod = Qnil;

static VALUE my_square(VALUE self, VALUE x)
{
	int ix = NUM2INT(x);
	int ret = square(ix);
	return INT2NUM(ret);
}

static VALUE my_cube(VALUE self, VALUE x)
{
	int ix = NUM2INT(x);
	int ret = cube(ix);
	return INT2NUM(ret);
}

static VALUE my_print(VALUE self, VALUE size, VALUE array)
{
	int csize = NUM2INT(size);

	double *carray = (double *) malloc(size * sizeof(double));

	for(int i = 0; i < csize; ++i)
		carray[i] = NUM2DBL(rb_ary_entry(array, i));

	print(csize, carray);

	free(carray);
}

static VALUE my_printstr(VALUE self, VALUE string)
{
	char *mystring = StringValueCStr(string);
	printstr(mystring);
}

void Init_moduleruby()
{
	mod = rb_define_module("ModuleRuby");
	rb_define_module_function(mod, "square", my_square, 1);
	rb_define_module_function(mod, "cube", my_cube, 1);
	rb_define_module_function(mod, "print", my_print, 2);
	rb_define_module_function(mod, "printstr", my_printstr, 1);
}
