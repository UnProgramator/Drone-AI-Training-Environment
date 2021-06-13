#pragma once
#include "CommunicationInterface.h"

class KeyboardController :
    public DataCoolectorInterface,
	public default_CommunicationInterface
{
private:
	std::ostream* outStrim;

public:
	KeyboardController();
	virtual ~KeyboardController() {};
	
	virtual void init_parser(int elementCount) override;
	virtual void parse_double(const char* name, const double value) override;
	virtual void parse_double_array(const char* name, const std::vector<double>& value) override;

	virtual default_ReturnedValueFromStript call() override;
	virtual void give_feedback(const default_FeedbackType& newParams) override;

	
};

