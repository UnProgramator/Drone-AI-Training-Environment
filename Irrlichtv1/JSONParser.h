#pragma once

#include "Drone.h"
#include "ObjectFactory.h"
#include <memory>

class Base_JSONParser
{
private:
	DefaultObjectFactory* object_factory;
public:
	//constructors and destructors
	Base_JSONParser(DefaultObjectFactory* object_factory);
	virtual ~Base_JSONParser();

	Base_JSONParser(const Base_JSONParser&) = delete;
	Base_JSONParser(Base_JSONParser&&) = delete;

	Base_JSONParser& operator=(const Base_JSONParser&) = delete;
	Base_JSONParser& operator=(Base_JSONParser&&) = delete;

	//files parsers

	virtual Drone* parseDrone(const std::string& filePath);
};

