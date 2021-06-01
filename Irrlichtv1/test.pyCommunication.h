#pragma once
#include "CommunicationInterface.h"
#include <Python.h>

class pyCommunication :
    public default_CommunicationInterface,
	public DataCoolectorInterface
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
	pyCommunication(const char* path, uint16_t input_size, uint16_t output_size, float learning_rate);
	~pyCommunication();
	void finishCommunication();

	virtual void init_parser(int elementCount) override;

	virtual void parse_double(const char* name, const double value) override;
	virtual void parse_double_array(const char* name, const std::vector<double>& value) override;

	virtual default_ReturnedValueFromStript call() override;
	virtual void give_feedback(const default_FeedbackType& newParams) override;
};

