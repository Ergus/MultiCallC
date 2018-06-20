
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
