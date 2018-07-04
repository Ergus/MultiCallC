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

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <config.h>

#include "builtins.h"
#include "shell.h"
#include "bashgetopt.h"
#include "common.h"

#include "libfun.h"

int my_square(WORD_LIST *list)
{
	int argc;
	char **argv = make_builtin_argv(list, &argc);

	assert(argc == 2);

	int i = atoi(argv[1]);
	printf("%d\n", square(i));

	return (EXECUTION_SUCCESS);
}

int my_cube(WORD_LIST *list)
{
	int argc;
	char **argv = make_builtin_argv(list, &argc);

	assert(argc == 2);

	int i = atoi(argv[1]);

	printf("%d\n", cube(i));

	return (EXECUTION_SUCCESS);
}

int my_print(WORD_LIST *list)
{
	int argc;
	char **argv = make_builtin_argv(list, &argc);

	int size = atoi(argv[1]);

	double *arr = (double *) malloc(size * sizeof(double));

	assert(size + 2 == argc);

	for (int i = 0; i < size; ++i) {
		arr[i] = atof(argv[i+2]);
	}

	print(size, arr);

	return (EXECUTION_SUCCESS);
}

int my_printstr(WORD_LIST *list)
{
	int argc;
	char **argv = make_builtin_argv(list, &argc);

	assert(argc == 2);

	printstr(argv[1]);

	return (EXECUTION_SUCCESS);
}

// Documentation
char *square_doc[] = {
	"Sample builtin square function.",
	(char *)NULL
};

/* The standard structure describing a builtin command.  bash keeps an array
   of these structures.  The flags must include BUILTIN_ENABLED so the
   builtin can be used. */
struct builtin square_struct = {
	"square",		    /* builtin name */
	my_square,		    /* function implementing the builtin */
	BUILTIN_ENABLED,	/* initial flags for builtin */
	square_doc,		    /* array of long documentation strings. */
	"square",		    /* usage synopsis; becomes short_doc */
	0			        /* reserved for internal use */
};

struct builtin cube_struct = {
	"cube", my_cube, BUILTIN_ENABLED,
	NULL, "square",	0
};

struct builtin print_struct = {
	"print", my_print, BUILTIN_ENABLED,
	NULL, "print",	0
};

struct builtin printstr_struct = {
	"printstr", my_printstr, BUILTIN_ENABLED,
	NULL, "printstr",	0
};
