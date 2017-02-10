
#include <Python.h>
#include <libfun.h>

#include <stdlib.h>

// Define functions wrapper
static PyObject* my_square(PyObject* self, PyObject* args){  
    int value,answer;
    if (!PyArg_ParseTuple(args, "i", &value))
        return NULL;
  
    answer = square(value);
    return Py_BuildValue("i", answer);
    }

static PyObject* my_cube(PyObject* self, PyObject* args){
    int value, answer;
    if (!PyArg_ParseTuple(args, "i", &value))
        return NULL;
  
    answer = cube(value);;
    return Py_BuildValue("i", answer);
    }

static PyObject* my_print(PyObject* self, PyObject* args){
    PyObject* pyarray, *seq;
    int size;
  
    if (!PyArg_ParseTuple(args, "iO", &size,&pyarray))
        return NULL;

    double *array=(double*) malloc(size*sizeof(double));
  
    seq = PySequence_Fast(pyarray, "Expected a sequence");
    for(int i=0;i<size;i++){
        array[i]=PyFloat_AsDouble(PySequence_GetItem(seq,i));
        }

    print(size,array);
    free(array);
    return Py_BuildValue("");
    }

static PyObject* my_printstr(PyObject* self, PyObject* args){

    char *mystring;
    
    if (!PyArg_ParseTuple(args, "s", &mystring))
        return NULL;

    printstr(mystring);
  
    return Py_BuildValue("");
    }

//  define functions in module
static PyMethodDef MyMethods[] = {
    {"square", my_square, METH_VARARGS, "evaluate the cube function"},  
    {"cube", my_cube, METH_VARARGS, "evaluate the cube function"},
    {"print", my_print, METH_VARARGS, "print a double array"},
    {"printstr", my_printstr, METH_VARARGS, "print a double array"},  
    {NULL, NULL, 0, NULL}
    };

static struct PyModuleDef my_module_def ={
    PyModuleDef_HEAD_INIT,
    "my_module",                          /* name of module */
    "Modulo de prueba creado por mi",     /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    MyMethods
    };

PyMODINIT_FUNC PyInit_mymodule(void){
    return PyModule_Create(&my_module_def);
    }


