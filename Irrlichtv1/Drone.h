#pragma once

#include <irrlicht.h>
#include <string>
#include <list>
#include "DynamicObject.h"
#include "SensorInterface.h"
#include "ObjectControllerInterface.h"
#include "PhysicsManager.h"

class Drone : ObjectControllerInterface
{
private:
	DynamicObject* mesh = nullptr;
	float forward_ratio =0, rotation_ratio = 0, up_ratio = 0;

	PhysicsManager* phyMgr =nullptr;

	std::list<SensorInterface*> sensor_list;

public:
	const float maxFrowardSpeed = 0.01f;
	const float maxUpSpeed = 0.05f;
	const float maxRightRotationSpeed = 0.02f;

	Drone(const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation,  const irr::core::vector3df & initalOrientation, PhysicsManager* physiscsMgr);
	Drone(const std::string& meshPath, const std::string& textPath, const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df & initalOrientation, PhysicsManager* physiscsMgr);
	Drone(const std::string& meshPath, const std::string& textPath, const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df& scale,  const irr::core::vector3df & initalOrientation, PhysicsManager* physiscsMgr);

	bool verifyCollision(class StaticObject* otherObject);

	virtual void moveForwards(float ratio = 0.f);
	virtual void rotateRight(float ratio = 0.f);
	virtual void moveUp(float ratio = 0.f);

	virtual void add_sensor(SensorInterface* sensor);
	virtual void getSensorReadValues(default_CommunicationInterface& transmiter);

	virtual void tick(float deltaTime) override;
	virtual void reset(bool toDefault = true);

#pragma warning(need to be implemented)
	virtual irr::core::vector3df getVelocity() const;
	virtual float getForwardVelocity() const; 
	virtual irr::core::vector3df getAccelerations() const;
	virtual float getForwardAcceleration() const;
};

