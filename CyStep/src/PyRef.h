#include "Python.h"
#include <iostream>

namespace PyPtr {
    class PyRef {
        PyObject* obj;

        public:
            PyObject* get() const {return obj;}

            PyRef() {
                //std::cout << "Default ctor " << obj << std::endl;
                obj = NULL;
            }

            PyRef(PyObject* set_obj) : obj(set_obj) {
                //std::cout << "Obj ctor: " << obj << " ";
                Py_XINCREF(set_obj);
            }

            ~PyRef() {
                //std::cout << "Destructor " << obj << std::endl;
                Py_XDECREF(obj);
            }

            PyRef(const PyRef& other) {
                //std::cout << "Copy ctor " << obj << std::endl;
                obj = PySet_New(other.obj);
                Py_XINCREF(obj);
                Py_XDECREF(other.obj); //try
            }

            PyRef(PyRef&& other) {
                //std::cout << "Move ctor " << obj << std::endl;
                obj = other.obj;
                Py_XDECREF(other.obj);
            }

            PyRef& operator=(const PyRef& other) {
                //std::cout << "Assignment " << obj << std::endl;
                Py_XDECREF(obj);
                obj = other.obj;
                Py_XINCREF(obj);
                return *this;
            }

            PyRef& operator=(PyRef&& other) {
                //std::cout << "Move assignment " << obj << std::endl;
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
                Py_XINCREF(result.obj);
                return result;
            }

            bool operator== (const PyRef &other) const {
                //std::cout << "Equality" << std::endl;
                return PyObject_RichCompareBool(obj, other.obj, Py_EQ);
            }
    };
}