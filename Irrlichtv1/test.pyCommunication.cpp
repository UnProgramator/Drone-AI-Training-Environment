#include "test.pyCommunication.h"
#include <Python.h>
#include <string>

using std::operator""s;
#define CHECK_CREATED(var) if(!var) throw std::exception(("python variable "s+ #var +" at line  " + std::to_string(__LINE__) + " in file " + __FILE__ +" could not be created").c_str())

pyCommunication::pyCommunication(const char* path):
	func_arg(nullptr), is_running(true), crt_element(0)
{
	if (!path)
		throw std::exception("Error: path to python file not given");
	Py_Initialize();

	module = PyImport_ImportModule(path);
	if (!module) {
		finishCommunication();
		throw std::exception(("Error: module "s + path + " could not be imported").c_str());
	}

	call_func = PyObject_GetAttrString(module, "iterateNextGeneration");
	if (!call_func) {
		finishCommunication();
		throw std::exception("Error: object/function iterateNextGeneration not Found");
	}
	if (!PyCallable_Check(call_func)) {
		finishCommunication();
		throw std::exception("Error: object/function iterateNextGeneration not callable");
	}

	results_fuc = PyObject_GetAttrString(module, "getFeedback");
	if (!results_fuc) {
		finishCommunication();
		throw std::exception("Error: object/function getFeedback not Found");
	}
	if (!PyCallable_Check(results_fuc)) {
		finishCommunication();
		throw std::exception("Error: object/function getFeedback not callable");
	}

	//call the init function in python

	PyObject* init_func, * returnedValue;
	init_func = PyObject_GetAttrString(this->module, "init");
	if (!init_func) {
		finishCommunication();
		throw;
	}
	if (!PyCallable_Check(init_func)) {
		finishCommunication();
		throw;
	}

	returnedValue = PyObject_Call(init_func, PyTuple_New(0), nullptr);
	if (!returnedValue) {
		finishCommunication();
		throw std::exception("Error: Error occured. PyObject* was null");
	}
	if (!PyBool_Check(returnedValue)) {
		finishCommunication();
		throw std::exception("Exception: Invalid retunrd type. Returned type was no of type bool");
	}

	int compare_result = PyObject_RichCompareBool(returnedValue, Py_True, Py_EQ);
	if (compare_result != 1) { //!=1 pt ca pote returna -1 la eroare
		finishCommunication();
		throw std::exception(("Error: python call for init result in an error, value "s + std::to_string(compare_result) + " was returned by comparison function").c_str());
	}
	Py_DECREF(returnedValue);
	Py_DECREF(init_func);
}

pyCommunication::~pyCommunication()
{
	if(is_running) Py_Finalize();
}

void pyCommunication::finishCommunication()
{
	if (!is_running) return;
	is_running = false;
	//to be sure that all memory is corectly dealocated, i decrement the counter before ending the session
	//this may be unnecessary, but at this point I don't know very well how the Py C library work
	Py_XDECREF(func_arg);
	Py_XDECREF(module);
	Py_XDECREF(call_func);
	Py_XDECREF(results_fuc);
	Py_Finalize();
}


void pyCommunication::init_parser(int elementCount)
{
	Py_XDECREF(func_arg);
	func_arg = PyTuple_New(elementCount);
	CHECK_CREATED(func_arg);
	crt_element = 0;
}

void pyCommunication::addElemToTuple(PyObject* & tuple_entry) {
	PyTuple_SetItem(func_arg, crt_element, tuple_entry);
	crt_element++;
	Py_XDECREF(tuple_entry);
}

void pyCommunication::parse_double(const char* name, const double value)
{
	PyObject* tuple_entry, *tmp;
	tuple_entry = PyTuple_New(2);
	CHECK_CREATED(tuple_entry);

	PyTuple_SetItem(tuple_entry, 0, PyUnicode_FromString(name));
	PyTuple_SetItem(tuple_entry, 1, PyFloat_FromDouble(value));

	addElemToTuple(tuple_entry);
}

void pyCommunication::parse_double_array(const char* name, const std::vector<double>& value)
{
	PyObject *tuple_entry, *elements;
	tuple_entry = PyTuple_New(2);
	PyTuple_SetItem(tuple_entry, 0, PyUnicode_FromString(name));
	
	elements = PyTuple_New(value.size());
	CHECK_CREATED(elements);
	for (int i = 0; i < value.size(); i++)
		PyTuple_SetItem(elements, i, PyFloat_FromDouble(value[i]));

	PyTuple_SetItem(tuple_entry, 1, PyUnicode_FromString(name));

	addElemToTuple(tuple_entry);
}

void* pyCommunication::call()
{
	return nullptr;
}

void pyCommunication::give_results(void* newParams)
{
	default_newParams* parameters = (default_newParams*) newParams;
	PyObject* tuple;
	tuple = PyTuple_New(4);
	CHECK_CREATED(tuple);
	PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(parameters->new_pos[0]));
	PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(parameters->new_pos[1]));
	PyTuple_SetItem(tuple, 2, PyFloat_FromDouble(parameters->new_pos[2]));
	PyTuple_SetItem(tuple, 3, PyBool_FromLong(parameters->hasCollide));

	PyObject_Call(this->results_fuc, tuple, nullptr);

}



#undef CHECK_CREATED