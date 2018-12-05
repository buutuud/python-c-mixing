#include <Python.h>
#include "xxhash.h"

unsigned long long hash_calc(const void* buffer, size_t length)
{
    unsigned long long const seed = 0;   /* or any other value */
    unsigned long long const hash = XXH64(buffer, length, seed);
    return hash;
}

static PyObject *_hash_calc(PyObject* self, PyObject* args) {
    // Arguments
    // void * buffer; int length = 0;
    char* buffer; int length = 0;
    char ret_str[200];
    // Return value
    unsigned long long res;

    // If parse failure (0), return NULL
    if (!PyArg_ParseTuple(args, "si", &buffer, &length)) {
        return NULL;
    }

    // Call the actual method, store the result
    res = hash_calc(buffer, length);
    snprintf(ret_str,100,"%llx",res);
    // Wrap the return value into PyObject
    return Py_BuildValue("s", ret_str);
}

// Construct the Module's Method Table (list the methods to expose)
static PyMethodDef SpeedupPerformanceMethods[] = {
    // hash_calc method takes in both positional & keyword parameters
    {"hash_calc", _hash_calc, METH_VARARGS, "A xxhash method."},
    // Ends with an entry with NULL values
    {NULL, NULL, 0, NULL}
};

// Define the module structure
static struct PyModuleDef xxhash_module = {
    PyModuleDef_HEAD_INIT,
    "xxhash",
    "A module containing methods with faster performance.",
    -1, // global state
    SpeedupPerformanceMethods
};

// Init method to be called when module gets imported in Python
PyMODINIT_FUNC PyInit_xxhash() {
    return PyModule_Create(&xxhash_module);
}
