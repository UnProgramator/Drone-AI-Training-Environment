#pragma once

#include "SensorInterface.h"

class DistanceSensor : public SensorInterface {
private:
	StaticObject* meshObj, * rangeObj;
public:
	using vector3df = irr::core::vector3df;
	DistanceSensor(const std::string& sensorMeshPath, irr::scene::ISceneNode* parent, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range, const char* name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
};

class GPS : public SensorInterface {
private:
	StaticObject* parent;
public:
	GPS(StaticObject* parent, const char* name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
};

class Altimeter : public SensorInterface {
private:
	StaticObject* parent;
public:
	Altimeter(StaticObject* parent, const char* name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
};