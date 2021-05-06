#pragma once

#include "SensorInterface.h"
#include "Drone.h"
#include "ObjectControllerInterface.h"

class DefaultObjectFactory
{
public:
	virtual SensorInterface* getSensor(std::string& name);
	virtual Drone* getDrone();
	virtual StaticObject* getStaticObject();
	virtual DynamicObject* getDynamicObject();
	virtual ObjectControllerInterface* getAI(const std::string& name);
};

