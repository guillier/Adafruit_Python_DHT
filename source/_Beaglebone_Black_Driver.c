// Copyright (c) 2014 Adafruit Industries
// Author: Tony DiCola

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <Python.h>

#include "Beaglebone_Black/bbb_dht_read.h"

// Wrap calling dht_read function and expose it as a DHT.read Python module & function.
static PyObject* Beaglebone_Black_Driver_read(PyObject *self, PyObject *args)
{
	// Parse sensor and pin integer arguments.
    int sensor, base, number;
    if (!PyArg_ParseTuple(args, "iii", &sensor, &base, &number)) {
        return NULL;
    }
    // Call dht_read and return result code, humidity, and temperature.
    float humidity = 0, temperature = 0;
    int result = bbb_dht_read(sensor, base, number, &humidity, &temperature);
    return Py_BuildValue("iff", result, humidity, temperature);
}

// Boilerplate python module method list and initialization functions below.

static PyMethodDef module_methods[] = {
    {"read", Beaglebone_Black_Driver_read, METH_VARARGS, "Read DHT sensor value on a Beaglebone Black."},
    {NULL, NULL, 0, NULL}
};

#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "Beaglebone_Black_Driver", /* m_name */
        NULL,                  /* m_doc */
        -1,                    /* m_size */
        module_methods,        /* m_methods */
        NULL,                  /* m_reload */
        NULL,                  /* m_traverse */
        NULL,                  /* m_clear */
        NULL,                  /* m_free */
    };

    PyMODINIT_FUNC PyInit_Beaglebone_Black_Driver(void)
    {
        return PyModule_Create(&moduledef);
    }
#else
    PyMODINIT_FUNC initBeaglebone_Black_Driver(void)
    {
        Py_InitModule("Beaglebone_Black_Driver", module_methods);
    }
#endif
