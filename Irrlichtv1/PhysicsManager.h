#pragma once

#include <irrlicht.h>
#include <list>
#include "PysicsComponentInterface.h"

class PhysicsManager
{
public:
	using vector3 = irr::core::vector3df;
protected:
	static const vector3 nullForce;
	static const vector3 zeroForce;

	vector3 velocity = nullForce,
		aceleration = nullForce,
		externForcesComposition = nullForce,
		internalForce = nullForce;
	vector3 forwardVector;

	double linearVelocity, linearAcceleration;

	std::list<PysicsComponentInterface*> external_forces;

public:
	const double maxAcceleration, maxVelocity;
	
	virtual void computeExternalForce();
	virtual vector3 getExternalForces() const { return externForcesComposition; }

	virtual void computeInternalForces(double rotationAngle, double forwardCommand, double UpCommand, double deltaTime);

	virtual void computeDroneVelocity(double deltaTime);
	virtual vector3 getVelocity()const { return velocity; }
	virtual vector3 getAcceleration()const { return aceleration; }
	virtual vector3 getNewForwardVector()const { return forwardVector; }

	virtual void computeNextPosition(vector3 position);

	virtual void addExternalForceReference(PysicsComponentInterface* force) { external_forces.push_back(force); }

	virtual void delete_external_forces();
};

PhysicsManager* getDefaultPsysicsManagerInstanciation();

