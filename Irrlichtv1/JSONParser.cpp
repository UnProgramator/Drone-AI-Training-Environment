#include "JSONParser.h"
#include "ObjectFactory.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using Json = nlohmann::json;

Base_JSONParser::Base_JSONParser(DefaultObjectFactory* object_factory):
	object_factory{object_factory}
{
}

Base_JSONParser::~Base_JSONParser()
{
}

Drone* Base_JSONParser::parseDrone(const std::string& filePath)
{
	Drone* drone;
	Json json; 
	{
		std::ifstream fin(filePath);
		fin >> json;
		fin.close();
	}
	drone = object_factory->getDrone(json);
	for (auto& sensor : json["sensors"]) {
		std::string name = sensor["name"].get<std::string>();
		auto& atribs = sensor["attributes"];
		drone->add_sensor(object_factory->getSensor(name, atribs));
	}
	return drone;
}
