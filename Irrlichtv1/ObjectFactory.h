#pragma once

#include <nlohmann/json.hpp>
#include "SensorInterface.h"
#include "Drone.h"
#include "ObjectControllerInterface.h"


class DefaultObjectFactory
{
public:
	using Json = nlohmann::json;
	virtual SensorInterface* getSensor(std::string& name, Json& atributes);
	virtual Drone* getDrone(Json& atributes);
	virtual StaticObject* getStaticObject(Json& atributes, const std::string& name, const bool bHasCollision = true, const bool bAddToRaycast=true);
	virtual DynamicObject* getDynamicObject(Json& atributes, const std::string& name, const bool bHasCollision = true, const bool bAddToRaycast=true);
	virtual ObjectControllerInterface* getAI(const std::string& name, Json& atributes);
};

