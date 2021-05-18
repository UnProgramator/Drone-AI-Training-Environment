#pragma once

#include "SensorInterface.h"
#include "Drone.h"

class DistanceSensor : public SensorInterface {
private:
	StaticObject* meshObj, * rangeObj;
public:
	using vector3df = irr::core::vector3df;
	DistanceSensor(const std::string& sensorMeshPath, const std::string& sensorTexturePath, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range, const std::string& name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
	virtual bool link_to(const StaticObject* objectToLinkTo) override;
};

class GPS : public SensorInterface {
private:
	const StaticObject* parent;
public:
	GPS(const std::string& name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
	virtual bool link_to(const StaticObject* objectToLinkTo) override;
};

class Altimeter : public SensorInterface {
private:
	const StaticObject* parent;
public:
	Altimeter(const std::string& name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
	virtual bool link_to(const StaticObject* objectToLinkTo) override;
};

class Velocimometer : public SensorInterface {
private:
	const StaticObject* parent;
	const Drone* parentDrone;
public:
	Velocimometer(const std::string& name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
	virtual bool link_to(const StaticObject* objectToLinkTo) override;
	void link_to(const Drone* parentDrone);
};

class Accelerometer : public SensorInterface {
private:
	const StaticObject* parent;
	const Drone* parentDrone;
public:
	Accelerometer(const std::string& name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
	virtual bool link_to(const StaticObject* objectToLinkTo) override;
	void link_to(const Drone* parentDrone);
};

class Accelerometer3D : public SensorInterface {
private:
	const StaticObject* parent;
	const Drone* parentDrone;
public:
	Accelerometer3D(const std::string& name);

	virtual void getDetectedValue(DataCoolectorInterface& ci) override;
	virtual bool link_to(const StaticObject* objectToLinkTo) override;
	void link_to(const Drone* parentDrone);
};