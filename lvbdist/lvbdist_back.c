#include <Python.h>
#include "lvbdistcalcs/prob_func.h"


/** wrap prob_func */

#define LVBDIST_PROVIDE(RAWNAME) \
    static PyObject *methodext_##RAWNAME(PyObject *self, PyObject *args)

#define LVBDIST_SCAN_ARG_AND_DECLARE(FORMAT, DECLARE, ...) \
        probability base, additional; \
        int threshold; \
        DECLARE; \
        if (!PyArg_ParseTuple(args, "ddi"FORMAT, &base, &additional, &threshold, ##__VA_ARGS__)) \
            return NULL

#define LVBDIST_DEF_MODEL() \
        LVBdistribution dist = create_model(base, additional, threshold)

#define LVBDIST_RETURN(FUNCNAME, ...) \
        LVBDIST_DEF_MODEL(); \
        return PyFloat_FromDouble(FUNCNAME(&dist, ##__VA_ARGS__))


/** export functions definition */

LVBDIST_PROVIDE(max_times) {
    LVBDIST_SCAN_ARG_AND_DECLARE("",  );
    LVBDIST_DEF_MODEL();
    return PyLong_FromLong((long)dist.max_times);
}

LVBDIST_PROVIDE(have_success_given_no_successes_before) {
    LVBDIST_SCAN_ARG_AND_DECLARE("i", int n, &n);
    LVBDIST_RETURN(have_success_given_no_successes_before, n);
}

LVBDIST_PROVIDE(have_first_success_at_n) {
    LVBDIST_SCAN_ARG_AND_DECLARE("i", int n, &n);
    LVBDIST_RETURN(have_first_success_at_n, n);
}

LVBDIST_PROVIDE(have_first_success_at_n_E) {
    LVBDIST_SCAN_ARG_AND_DECLARE("", );
    LVBDIST_RETURN(have_first_success_at_n_E);
}

LVBDIST_PROVIDE(have_success_within_n_attempts) {
    LVBDIST_SCAN_ARG_AND_DECLARE("i", int n, &n);
    LVBDIST_RETURN(have_success_within_n_attempts, n);
}

LVBDIST_PROVIDE(have_m_successes_within_n_attempts) {
    LVBDIST_SCAN_ARG_AND_DECLARE("ii", int n;int m, &n, &m);
    LVBDIST_RETURN(have_m_successes_within_n_attempts, n, m);
}

LVBDIST_PROVIDE(have_m_or_more_successes_within_n_attempts) {
    LVBDIST_SCAN_ARG_AND_DECLARE("ii", int n;int m, &n, &m);
    LVBDIST_RETURN(have_m_or_more_successes_within_n_attempts, n, m);
}

LVBDIST_PROVIDE(have_m_successes_within_n_attempts_E) {
    LVBDIST_SCAN_ARG_AND_DECLARE("i", int n, &n);
    LVBDIST_RETURN(have_m_successes_within_n_attempts_E, n);
}

LVBDIST_PROVIDE(have_special_success_within_n_attempts) {
    LVBDIST_SCAN_ARG_AND_DECLARE("id", int n;probability p, &n, &p);
    if (p <= 0 || p >= 1) {
        PyErr_SetString(PyExc_ValueError, "Invalid probability");
        return NULL;
    }
    LVBDIST_RETURN(have_special_success_within_n_attempts, n, p);
}

LVBDIST_PROVIDE(have_special_success_within_n_attempts_E) {
    LVBDIST_SCAN_ARG_AND_DECLARE("d", probability p, &p);
    if (p <= 0 || p >= 1) {
        PyErr_SetString(PyExc_ValueError, "Invalid probability");
        return NULL;
    }
    LVBDIST_RETURN(have_special_success_within_n_attempts_E, p);
}


/** table for exported c functions */

static PyMethodDef LvbdistMethodexts[] = {
    { "cmax_times", methodext_max_times, METH_VARARGS, "" },
    { "chave_success_given_no_successes_before", methodext_have_success_given_no_successes_before, METH_VARARGS, "" },
    { "chave_first_success_at_n", methodext_have_first_success_at_n, METH_VARARGS, "" },
    { "chave_first_success_at_n_E", methodext_have_first_success_at_n_E, METH_VARARGS, "" },
    { "chave_success_within_n_attempts", methodext_have_success_within_n_attempts, METH_VARARGS, "" },
    { "chave_m_successes_within_n_attempts", methodext_have_m_successes_within_n_attempts, METH_VARARGS, "" },
    { "chave_m_or_more_successes_within_n_attempts", methodext_have_m_or_more_successes_within_n_attempts, METH_VARARGS, "" },
    { "chave_m_successes_within_n_attempts_E", methodext_have_m_successes_within_n_attempts_E, METH_VARARGS, "" },
    { "chave_special_success_within_n_attempts", methodext_have_special_success_within_n_attempts, METH_VARARGS, "" },
    { "chave_special_success_within_n_attempts_E", methodext_have_special_success_within_n_attempts_E, METH_VARARGS, "" },
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
