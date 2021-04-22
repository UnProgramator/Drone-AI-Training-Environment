#pragma once

#include <string>
#include <vector>
#include <typeinfo>

class DataCoolectorInterface {
public:
	virtual void parse_double(const char* name, const double value) = 0;
	virtual void parse_double_array(const char* name, const std::vector<double>& value) = 0;
};

//interface to be implemented and given back to the library in order to comunicate with the ai script
template<typename ReturnedValueFromStript, typename FeedbackType>
class CommunicationInterface:public DataCoolectorInterface {
public:
	virtual void init_parser(int elementCount) = 0;
	virtual ReturnedValueFromStript call() =0;
	virtual void give_feedback(const FeedbackType & newParams) = 0;

	//from DataCoolectorInterface
	virtual void parse_double(const char* name, const double value) = 0;
	virtual void parse_double_array(const char* name, const std::vector<double>& value) = 0;
};

struct default_FeedbackType {
	double new_pos[3];
	bool hasCollide;
	default_FeedbackType(double new_pos[3], bool hasCollide) : hasCollide{ hasCollide } { memcpy(this->new_pos, new_pos, 3 * sizeof(double)); }
	default_FeedbackType(double new_pos_X, double new_pos_Y, double new_pos_Z, bool hasCollide) :
		hasCollide{ hasCollide } {
		new_pos[0] = new_pos_X;
		new_pos[1] = new_pos_Y;
		new_pos[2] = new_pos_Z;
	}
};

struct default_ReturnedValueFromStript {

};

typedef CommunicationInterface< default_ReturnedValueFromStript, default_FeedbackType> default_CommunicationInterface;