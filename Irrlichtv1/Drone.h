#pragma once

#include <irrlicht.h>
#include "DynamicObject.h"
#include "SensorInterface.h"

class Drone
{
private:
	DynamicObject* mesh;

public:
	const float maxFrowardSpeed = 0.1f;
	const float maxUpSpeed = 0.05f;
	const float maxRightRotationSpeed = 0.01f;

	Drone(const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation,  const irr::core::vector3df & initalOrientation);

	bool verifyCollision(class StaticObject* otherObject);

	virtual void moveForwards(float ratio=1.f);
	virtual void rotateRight(float ratio = 1.f);
	virtual void moveUp(float ratio = 1.f);

	virtual void add_sensor(SensorInterface*);
};

