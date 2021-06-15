#pragma once

#include <irrlicht.h>
#include <string>
#include <list>
#include "DynamicObject.h"
#include "SensorInterface.h"
#include "ObjectControllerInterface.h"
#include "PhysicsManager.h"
#include "DefaultPhysicsComponents.h"

class Drone : ObjectControllerInterface
{
public:
	
	using DroneAttributes = DronePhysicsManager::DroneAttributes;
private:
	DynamicObject* mesh = nullptr;
	default_ReturnedValueFromStript las_given_comand = {};

	DronePhysicsManager* dronePhyMgr = nullptr;

	std::list<SensorInterface*> sensor_list;

	void no_physics_tick(float deltaTime); // old model that do not use physics

public:
	const DroneAttributes atributes;

	Drone(const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation,  const irr::core::vector3df & initalOrientation, const DroneAttributes& atributes);
	Drone(const std::string& meshPath, const std::string& textPath, 
			const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df & initalOrientation, 
		const DroneAttributes& atributes);
	Drone(const std::string& meshPath, const std::string& textPath, 
			const irr::core::vector3df & initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df& scale,  const irr::core::vector3df & initalOrientation, 
		const DroneAttributes& atributes);
	virtual ~Drone();

	bool verifyCollision(class StaticObject* otherObject);

	virtual int getSensorsNumberOfOutputValues();
	virtual int getSensorsNumber() { return sensor_list.size(); }
	virtual int getNumberOfInputs(){ return 3; }
	virtual bool setChieldMesh(StaticObject*) const;
	virtual const irr::core::vector3df& getPosition() const { return mesh->getPosition(); }

	virtual void add_sensor(SensorInterface* sensor);
	virtual void getSensorReadValues(DataCoolectorInterface& transmiter);

	virtual bool giveCommands(default_ReturnedValueFromStript& values);

	virtual void tick(float deltaTime) override;
	
	virtual void reset(bool toDefault = false);

	virtual irr::core::vector3df getVelocity() const;
	virtual float getForwardVelocity() const; 
	virtual irr::core::vector3df getAccelerations() const;
	virtual float getForwardAcceleration() const;

	irr::core::vector3df getForwardVector() const { return mesh->getForwardVector(); }
};

