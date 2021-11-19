#include "Python.h"

namespace PyPtr {
    class PyRef {
        PyObject* obj;

        public:
            PyObject* get() const {return obj;}

            PyRef() {
                obj = PySet_New(NULL);
                Py_XINCREF(obj);
            }

            PyRef(PyObject* set_obj) : obj(set_obj) {
                Py_XINCREF(set_obj);
            }

            ~PyRef() {
                Py_XDECREF(obj);obj = NULL;
            }

            PyRef(const PyRef& other) : obj(other.obj)  {
                Py_XINCREF(other.obj);
            }

            PyRef(PyRef&& other) {
                obj = other.obj;
                other.obj = NULL;
            }

            PyRef& operator=(const PyRef& other) {
                Py_XDECREF(obj);
                obj = PySet_New(other.obj);
                Py_XINCREF(obj);
                return *this;
            }

            PyRef& operator=(PyRef&& other) {
                Py_XDECREF(obj);
                obj = PySet_New(other.obj);
                Py_XINCREF(obj);
                other.obj = NULL;
                return *this;
            }

            PyRef& operator+= (const PyRef& other) {
                _PySet_Update(this->obj, PyObject_GetIter(other.obj));
                return *this;
            }

            PyRef operator+ (const PyRef& other) {
                PyRef result(PySet_New(obj));
                _PySet_Update(result.obj, PyObject_GetIter(other.obj));
                return result;
            }

            bool operator== (const PyRef &other) const {
                return PyObject_RichCompareBool(obj, other.obj, Py_EQ);
            }
    };
}