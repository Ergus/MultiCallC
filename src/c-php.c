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

#include "php.h"
#include <libfun.h>

PHP_NAMED_FUNCTION(my_square)
{
    long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &value) == FAILURE)
        RETURN_NULL();

    RETURN_LONG(square(value));
}

PHP_NAMED_FUNCTION(my_cube)
{
    long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &value) == FAILURE)
        RETURN_NULL();

    RETURN_LONG(cube(value));
}

PHP_NAMED_FUNCTION(my_print)
{
    long size;
	zval *arr, *zvalue;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "la", &size, &arr) == FAILURE)
        RETURN_NULL();

	double *carray = (double *) malloc(size * sizeof(double));

	for (int i = 0; i < size; ++i) {
		zvalue = zend_hash_index_find(Z_ARRVAL_P(arr), i);
		assert(Z_TYPE_P(zvalue) == IS_DOUBLE);

		carray[i] = Z_DVAL_P(zvalue);
    }

	print(size, carray);

	free(carray);
	RETURN_TRUE;
}

PHP_NAMED_FUNCTION(my_printstr)
{
	char *mystring;
	long len;   // Very important to use long and not int

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &mystring, &len) == FAILURE)
        RETURN_NULL();

	printstr(mystring);

	RETURN_TRUE;
}

/* compiled function list so Zend knows what's in this module */
zend_function_entry modulephp_functions[] =
{
	PHP_NAMED_FE(square, my_square, NULL)
	PHP_NAMED_FE(cube, my_cube, NULL)
	PHP_NAMED_FE(myprint, my_print, NULL)
	PHP_NAMED_FE(myprintstr, my_printstr, NULL)
    PHP_FE_END
};

/* compiled module information */
zend_module_entry modulephp_module_entry =
{
    STANDARD_MODULE_HEADER,
    "modulephp",
    modulephp_functions,
    NULL,   // Module init PHP_MINIT(counter)
    NULL,   // Module shutdown PHP_MINIT(counter)
    NULL,   // Request start PHP_RINIT(counter)
    NULL,   // Request end PHP_RSHUTDOWN(counter)
    NULL,   // Module Info PHP_MINFO(counter)
    "1.0",  // Version number
    STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(modulephp)

