#include <Python.h>
#include "xxhash.h"

unsigned long long slow_calc(const void* buffer, size_t length)
{
    unsigned long long const seed = 0;   /* or any other value */
    unsigned long long const hash = XXH64(buffer, length, seed);
    return hash;
}

// Define wrapper methods to be called in Python
// static PyObject *_slow_calc(PyObject *self, PyObject *args, PyObject *kwargs) {
//     // Arguments
//     void * buffer; int length = 0;
//     static char *kwlist[] = {"buffer", "length", NULL};
//     // Return value
//     unsigned long long res;

//     // If parse failure (0), return NULL
//     if (!PyArg_ParseTupleAndKeywords(args, kwargs, "K|s*i", kwlist, &buffer, &length)) {
//         return NULL;
//     }

//     // Call the actual method, store the result
//     res = slow_calc(buffer, length);

//     // Wrap the return value into PyObject
//     return Py_BuildValue("K", res);
// }

static PyObject *_slow_calc2(PyObject* self, PyObject* args) {
    // Arguments
    // void * buffer; int length = 0;
    char* buffer; int length = 0;
    
    // Return value
    unsigned long long res;

    // If parse failure (0), return NULL
    if (!PyArg_ParseTuple(args, "si", &buffer, &length)) {
        return NULL;
    }

    // Call the actual method, store the result
    res = slow_calc(buffer, length);

    // Wrap the return value into PyObject
    return Py_BuildValue("K", res);
}

// Construct the Module's Method Table (list the methods to expose)
static PyMethodDef SpeedupPerformanceMethods[] = {
    // slow_calc method takes in both positional & keyword parameters
    {"slow_calc", _slow_calc2, METH_VARARGS, "A slow calculation method."},
    // Ends with an entry with NULL values
    {NULL, NULL, 0, NULL}
};

// Define the module structure
static struct PyModuleDef speedup_performance_module = {
    PyModuleDef_HEAD_INIT,
    "speedup_performance",
    "A module containing methods with faster performance.",
    -1, // global state
    SpeedupPerformanceMethods
};

// Init method to be called when module gets imported in Python
PyMODINIT_FUNC PyInit_speedup_performance() {
    return PyModule_Create(&speedup_performance_module);
}
