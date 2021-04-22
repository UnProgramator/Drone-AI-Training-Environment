#pragma once

#include <string>
#include <vector>
#include <typeinfo>

//interface to be implemented and given back to the library in order to comunicate with the ai script
class CommunicationInterface {
public:
	virtual void parse_double(const char* name, const double value) =0;
	virtual void parse_double_array(const char* name, const std::vector<double>& value) =0;

	virtual void init_parser(int elementCount) = 0;
	virtual void* call() =0;
	virtual void give_results(void* newParams) = 0;
};

//this are the parameters given by the default drone ai controller as the void* to the CommunicationInterface::give_results()
//for changing the values given, you must define a new struct and extend the default drone ai controller or make an entire new one
//read the default drone ai controller for more informations
struct default_newParams {
	double new_pos[3];
	bool hasCollide;
	default_newParams(double new_pos[3], bool hasCollide) : hasCollide{ hasCollide } { memcpy(this->new_pos, new_pos, 3 * sizeof(double)); }
	default_newParams(double new_pos_X, double new_pos_Y, double new_pos_Z, bool hasCollide) :
		hasCollide{ hasCollide } {
		new_pos[0] = new_pos_X;
		new_pos[1] = new_pos_Y;
		new_pos[2] = new_pos_Z;
	}
};