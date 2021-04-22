#pragma once
#include "CommunicationInterface.h"
#include <Python.h>

class pyCommunication :
    public CommunicationInterface
{
private:
	bool is_running;
	uint8_t crt_element;
	PyObject* func_arg;
	PyObject* module;
	PyObject* call_func;
	PyObject* results_fuc;

	void addElemToTuple(PyObject* & tuple_entry);

public:
	pyCommunication(const char* path);
	~pyCommunication();
	void finishCommunication();

	virtual void init_parser(int elementCount) override;

	virtual void parse_double(const char* name, const double value) override;
	virtual void parse_double_array(const char* name, const std::vector<double>& value) override;

	virtual void* call() override;
	virtual void give_results(void* newParams) override;
};

