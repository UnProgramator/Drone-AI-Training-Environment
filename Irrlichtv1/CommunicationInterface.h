#pragma once

#include <string>
#include <vector>
#include <typeinfo>

class CommunicationInterface {
public:
	virtual void parse_integer(const std::string& name, const long value) =0;
	virtual void parse_double(const std::string& name, const double value) =0;
	virtual void parse_integer_array(const std::string& name, const std::vector<long>& value) =0;
	virtual void parse_double_array(const std::string& name, const std::vector<double>& value) =0;

	virtual void parse_generic(std::string& name,const std::type_info& typeInfo, const void*) =0; //to be implemented if needed
};