/*
 * hello.c -- A minimal Tcl C extension.
 */
#include <tcl.h>
#include <libfun.h>
#include <stdlib.h>
#include <assert.h>

static int my_square(ClientData cdata, Tcl_Interp *interp,
                     int objc, Tcl_Obj *const objv[])
{
	int x;

	if (objc != 2) {  // Arguments count
		Tcl_WrongNumArgs (interp, 1, objv, "i");
		return TCL_ERROR;
	}

	if (TCL_OK != Tcl_GetIntFromObj(interp, objv[1], &x))
		return TCL_ERROR;

	Tcl_Obj *res = Tcl_NewIntObj(square(x));

	Tcl_SetObjResult(interp, res);
	return TCL_OK;
}

static int my_cube(ClientData cdata, Tcl_Interp *interp,
                     int objc, Tcl_Obj *const objv[])
{
	int x;

	if (objc != 2) {  // Arguments count
		Tcl_WrongNumArgs (interp, 1, objv, "i");
		return TCL_ERROR;
	}

	if (TCL_OK != Tcl_GetIntFromObj(interp, objv[1], &x))
		return TCL_ERROR;

	Tcl_Obj *res = Tcl_NewIntObj(cube(x));

	Tcl_SetObjResult(interp, res);
	return TCL_OK;
}

static int my_print(ClientData cdata, Tcl_Interp *interp,
                   int objc, Tcl_Obj *const objv[])
{
	int size;
	double *array;

	if (objc < 2) {  // Arguments count
		Tcl_WrongNumArgs (interp, 1, objv, "i");
		return TCL_ERROR;
	}

	if (TCL_OK != Tcl_GetIntFromObj(interp, objv[1], &size))
		return TCL_ERROR;

	int Largc, code;
	char **Largv;
	char *string = Tcl_GetString(objv[2]);

	code = Tcl_SplitList(interp, string, &Largc, &Largv);

	if (code == TCL_ERROR)
		return TCL_ERROR;

	assert(Largc == size);

	array = (double *) malloc(size * sizeof(double));

	for (int i = 0; i < size; ++i) {
		array[i] = atof(Largv[i]);
	}

	print(size, array);

	Tcl_Free((char *) Largv);
	free(array);

	return TCL_OK;
}

static int my_printstr(ClientData cdata, Tcl_Interp *interp,
                       int objc, Tcl_Obj *const objv[])
{
	if (objc != 2) {  // Arguments count
		Tcl_WrongNumArgs (interp, 1, objv, "i");
		return TCL_ERROR;
	}

	char *string = Tcl_GetString(objv[2]);

	printstr(string);

	return TCL_OK;
}

// Module
int DLLEXPORT Moduletcl_Init(Tcl_Interp *interp)
{
	if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL)
		return TCL_ERROR;

	/* changed this to check for an error - GPS */
	if (Tcl_PkgProvide(interp, "moduletcl", "1.0") == TCL_ERROR)
		return TCL_ERROR;

	Tcl_CreateObjCommand(interp, "square", my_square, NULL, NULL);
	Tcl_CreateObjCommand(interp, "cube", my_cube, NULL, NULL);
	Tcl_CreateObjCommand(interp, "print", my_print, NULL, NULL);
	Tcl_CreateObjCommand(interp, "printstr", my_printstr, NULL, NULL);
	return TCL_OK;
}
