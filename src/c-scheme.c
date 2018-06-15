
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

SCM my_print(SCM x)
{
	//scm_to_
	//scm_from_int(cube(scm_to_int(x)));
}

void init_module()
{
	scm_c_define_gsubr("square", 1, 0, 1, my_square);
	scm_c_define_gsubr("cube", 1, 0, 1, my_cube);
	scm_c_define_gsubr("print", 1, 0, 0, my_print);
}
