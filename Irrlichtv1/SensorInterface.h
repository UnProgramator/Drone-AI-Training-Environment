#pragma once

#include <irrlicht.h>
#include <string>
#include "StaticObject.h"
#include "CommunicationInterface.h"

class SensorInterface { //not realy an interface after all...
protected:
	std::string name;

public:

	static void setSensorsRangeVisibility(bool isVisible = true);
	static void toggleSensorsRangeVisibility();
	static void addEntityToRangeVisibilityList(StaticObject* obj);

	virtual void getDetectedValue(CommunicationInterface&) =0;
	virtual const std::string& getName() const { return name; }

	SensorInterface(const char* name);

	virtual ~SensorInterface() =default;
};

class DistanceSensor : public SensorInterface {
private:
	StaticObject *meshObj, *rangeObj;
public:
	using vector3df = irr::core::vector3df;
	DistanceSensor(const std::string& sensorMeshPath, irr::scene::ISceneNode* parent, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range, const char*name);

	virtual void getDetectedValue(CommunicationInterface& ci) override;
};

class GPS : public SensorInterface {
private:
	StaticObject* parent;
public:
	GPS(StaticObject* parent, const char* name);

	virtual void getDetectedValue(CommunicationInterface& ci) override;
};

class Altimeter : public SensorInterface {
private:
	StaticObject* parent;
public:
	Altimeter(StaticObject* parent, const char* name);

	virtual void getDetectedValue(CommunicationInterface& ci) override;
};