#pragma once

#include <irrlicht.h>
#include <string>
#include <list>
#include <Python.h>
#include "DynamicObject.h"
#include "SensorInterface.h"

class Drone
{
private:
	DynamicObject* mesh = nullptr;
	float forward_ratio =0, rotation_ratio = 0, up_ratio = 0;
	
	std::list<DistanceSensor*> sensor_list;

public:
	const float maxFrowardSpeed = 0.01f;
	const float maxUpSpeed = 0.05f;
	const float maxRightRotationSpeed = 0.02f;

	Drone(const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation,  const irr::core::vector3df & initalOrientation);
	Drone(const std::string& path, const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation,  const irr::core::vector3df & initalOrientation);

	bool verifyCollision(class StaticObject* otherObject);

	virtual void moveForwards(float ratio = 0.f);
	virtual void rotateRight(float ratio = 0.f);
	virtual void moveUp(float ratio = 0.f);

	virtual void add_sensor(DistanceSensor* sensor);
	virtual class std::list<float> getDistanceSensorValues();
	virtual PyObject* getSensorReadValues();

	virtual irr::scene::ISceneNode* getParent();

	virtual void tick();
};

