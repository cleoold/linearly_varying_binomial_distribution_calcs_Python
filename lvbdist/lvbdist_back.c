#include <Python.h>
#include "lvbdistcalcs/prob_func.h"


/** wrap prob_func */

#define LVBDIST_SCAN_ARG_AND_GET_MODEL(FORMAT, DECLARE, ...) \
    probability base, additional; \
    int threshold; \
    LVBdistribution dist; \
    DECLARE; \
    if (!PyArg_ParseTuple(args, "ddi"FORMAT, &base, &additional, &threshold, ##__VA_ARGS__)) \
        return NULL; \
    dist = create_model(base, additional, threshold)



static PyObject *methodext_max_times(PyObject *self, PyObject *args) {
    LVBDIST_SCAN_ARG_AND_GET_MODEL("",  );
    return PyLong_FromLong((long)dist.max_times);
}

static PyObject *methodext_have_success_given_no_successes_before(PyObject *self, PyObject *args) {
    LVBDIST_SCAN_ARG_AND_GET_MODEL("i", int n, &n);
    return PyFloat_FromDouble(have_success_given_no_successes_before(&dist, n));
}

static PyObject *methodext_have_first_sucess_at_n(PyObject *self, PyObject *args) {
    LVBDIST_SCAN_ARG_AND_GET_MODEL("i", int n, &n);
    return PyFloat_FromDouble(have_first_success_at_n(&dist, n));
}

static PyObject *methodext_have_first_sucess_at_n_E(PyObject *self, PyObject *args) {
    LVBDIST_SCAN_ARG_AND_GET_MODEL("", );
    return PyFloat_FromDouble(have_first_success_at_n_E(&dist));
}

static PyObject *methodext_have_success_within_n_attempts(PyObject *self, PyObject *args) {
    LVBDIST_SCAN_ARG_AND_GET_MODEL("i", int n, &n);
    return PyFloat_FromDouble(have_success_within_n_attempts(&dist, n));
}


/** table for exported c functions */

static PyMethodDef LvbdistMethodexts[] = {
    { "cmax_times", methodext_max_times, METH_VARARGS, "" },
    { "chave_success_given_no_successes_before", methodext_have_success_given_no_successes_before, METH_VARARGS, "" },
    { "chave_first_sucess_at_n", methodext_have_first_sucess_at_n, METH_VARARGS, "" },
    { "chave_first_sucess_at_n_E", methodext_have_first_sucess_at_n_E, METH_VARARGS, "" },
    { "chave_success_within_n_attempts", methodext_have_success_within_n_attempts, METH_VARARGS, "" },
    { NULL, NULL, 0, NULL }
};

/** export module */

static struct PyModuleDef lvbdistmodule = {
    PyModuleDef_HEAD_INIT, "_lvbdist", "Python interface for lvbdist_calcs", -1, LvbdistMethodexts
};

PyObject *PyInit__lvbdist(void) {
    PyObject *module = PyModule_Create(&lvbdistmodule);
    return module;
}
