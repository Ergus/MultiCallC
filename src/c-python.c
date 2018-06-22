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

#include <Python.h>
#include <libfun.h>

#include <stdlib.h>

// Define functions wrapper
static PyObject *my_square(PyObject *self, PyObject *args)
{
	int value = PyLong_AsLong(args);

	if (value == -1 && PyErr_Occurred())
		return NULL;

	int answer = square(value);

	return Py_BuildValue("i", answer);
}

static PyObject *my_cube(PyObject *self, PyObject *args)
{
	int value, answer;
	if (!PyArg_ParseTuple(args, "i", &value))
		return NULL;

	answer = cube(value);
	return Py_BuildValue("i", answer);
}

static PyObject *my_print(PyObject *self, PyObject *args)
{
	PyObject *pyarray, *seq;
	int size;

	if (!PyArg_ParseTuple(args, "iO", &size, &pyarray))
		return NULL;

	double *array = (double *) malloc(size * sizeof(double));

	seq = PySequence_Fast(pyarray, "Expected a sequence");
	for(int i = 0; i < size; ++i)
		array[i] = PyFloat_AsDouble(PySequence_GetItem(seq, i));

	print(size, array);
	free(array);
	Py_RETURN_NONE;
}

static PyObject* my_printstr(PyObject *self, PyObject *args)
{
	char *mystring;

	if (!PyArg_ParseTuple(args, "s", &mystring))
		return NULL;

	printstr(mystring);
	Py_RETURN_NONE;
}

//  define functions in module
static PyMethodDef MyMethods[] = {
	{"square", my_square, METH_O, "evaluate the cube function"},
	{"cube", my_cube, METH_VARARGS, "evaluate the cube function"},
	{"print", my_print, METH_VARARGS, "print a double array"},
	{"printstr", my_printstr, METH_VARARGS, "print a double array"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef my_module_def = {
	PyModuleDef_HEAD_INIT,
	"modulepython",                       /* name of module */
	"Modulo de prueba creado por mi",     /* module documentation, may be NULL */
	-1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
	MyMethods
};

PyMODINIT_FUNC PyInit_modulepython(void)
{
	return PyModule_Create(&my_module_def);
}


