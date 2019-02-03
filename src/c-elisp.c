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

#include "emacs-module.h"
#include "libfun.h"

#include <string.h>
#include <ctype.h>
#include <unistr.h>
#include <assert.h>

int plugin_is_GPL_compatible;


static void provide(emacs_env *env, const char *feature)
{
	emacs_value Qfeat = env->intern(env, feature);
	emacs_value Qprovide = env->intern(env, "provide");
	emacs_value args[] = { Qfeat };

	env->funcall(env, Qprovide, 1, args);
}

static bool make_string(emacs_env *env, const char *contents, size_t size,
						emacs_value *result)
{
	if (size > PTRDIFF_MAX) {
		env->non_local_exit_signal (env, env->intern (env, "overflow-error"),
									env->intern (env, "nil"));
		return false;
    }
	if (u8_check ((const uint8_t *) contents, size) != NULL) {
		env->non_local_exit_signal (env, env->intern (env, "wrong-type-argument"),
									env->intern (env, "nil"));
		return false;
    }
	*result = env->make_string(env, contents, (ptrdiff_t) size);
	return env->non_local_exit_check (env) == emacs_funcall_exit_return;
}

static bool intern(emacs_env *env, const char *name, size_t size, emacs_value *result)
{
	bool simple = true;
	for (size_t i = 0; i < size; ++i)
		if (name[i] == '\0' || !isascii (name[i])) {
			simple = false;
			break;
		}
	if (simple)
		*result = env->intern (env, name);
	else {
		emacs_value string_object;
		/* ‘make_string’ from above. */
		if (!make_string (env, name, size, &string_object))
			return false;
		*result = env->funcall (env, env->intern (env, "intern"),
								1, &string_object);
    }
	return env->non_local_exit_check (env) == emacs_funcall_exit_return;
}

typedef emacs_value (*emacs_subr) (emacs_env *env,
                                   ptrdiff_t nargs, emacs_value *args,
                                   void *data) ;


static bool defun (emacs_env *env, const char *symbol_name,
				   ptrdiff_t min_arity, ptrdiff_t max_arity, emacs_subr function,
				   const char *documentation, void *data)
{
	emacs_value symbol;
	/* ‘intern’ from above. */
	if (!intern(env, symbol_name, strlen(symbol_name), &symbol))
		return false;
	if (documentation != NULL
		&& u8_check ((const uint8_t *) documentation,
					 strlen (documentation)) != NULL)
    {
		env->non_local_exit_signal (env, env->intern (env, "wrong-type-argument"),
									env->intern (env, "nil"));
		return false;
    }
	emacs_value func = env->make_function(env, min_arity, max_arity,
										  function, documentation, data);
	emacs_value args[] = {symbol, func};
	env->funcall(env, env->intern(env, "defalias"), 2, args);
	return env->non_local_exit_check(env) == emacs_funcall_exit_return;
}


// Functions here!!

emacs_value my_square(emacs_env *env, ptrdiff_t nargs,
					  emacs_value args[], void *data)
{
	int x = env->extract_integer(env, args[0]);
	int iret = square(x);
	return env->make_integer(env, iret);
}

emacs_value my_cube(emacs_env *env, ptrdiff_t nargs,
					emacs_value args[], void *data)
{
	int x = env->extract_integer(env, args[0]);
	int iret = cube(x);
	return env->make_integer(env, iret);
}

emacs_value my_print(emacs_env *env, ptrdiff_t nargs,
					 emacs_value args[], void *data)
{

	size_t csize = env->extract_integer(env, args[0]);
	size_t size = env->vec_size(env, args[1]);

	assert(csize == size);

	double* carray = (double *) malloc(csize * sizeof(double));

	for (int i = 0; i < csize; ++i) {
		emacs_value valuei = env->vec_get(env, args[1], i);
		carray[i] = env->extract_float(env, valuei);
	}

	print(csize, carray);

	free(carray);

	emacs_value nil = env->intern (env, "nil");
	if (env->non_local_exit_check (env) != emacs_funcall_exit_return)
		return NULL;
	return nil;
}


emacs_value my_printstr(emacs_env *env, ptrdiff_t nargs,
						emacs_value args[], void *data)
{
	size_t len = 0;

	bool have_size = env->copy_string_contents(env, args[0], NULL, &len);
	assert(have_size);

	char *cmystring = (char *) malloc(len * sizeof(char));

	env->copy_string_contents(env, args[0], cmystring, &len);

	printstr(cmystring);

	free(cmystring);
}

int emacs_module_init(struct emacs_runtime *ert)
{
	assert (ert->size > 0);
	if ((size_t) ert->size < sizeof *ert)
		return 1;

	emacs_env *env = ert->get_environment(ert);
	assert (env->size > 0);
	if ((size_t) env->size < sizeof *env)
		return 2;

	defun(env, "square", 1, 1, my_square, "Square calculation", NULL);
	defun(env, "cube", 1, 1, my_cube, "Cube calculation", NULL);
	defun(env, "myprint", 2, 2, my_print, "Print array", NULL);
	defun(env, "myprintstr", 1, 1, my_printstr, "Print string", NULL);


	provide(env, "moduleelisp");

	return 0;
}

