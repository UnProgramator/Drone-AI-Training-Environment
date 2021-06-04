#pragma once
#include "CommunicationInterface.h"
class DebugingStubComunicator:public DataCoolectorInterface, public default_CommunicationInterface
{
public:
	virtual void init_parser(int elementCount);
	virtual void parse_double(const char* name, const double value);
	virtual void parse_double_array(const char* name, const std::vector<double>& value);

	virtual default_ReturnedValueFromStript call();
	virtual void give_feedback(const default_FeedbackType& newParams);
};

