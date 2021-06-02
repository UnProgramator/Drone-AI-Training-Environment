#pragma once

#include <irrlicht.h>
#include <list>
#include "PhysicsComponentInterface.h"

class PhysicsManager
{
public:
	using vector3 = irr::core::vector3df;
	static const vector3 nullForce;
	static const vector3 zeroForce;
protected:

	vector3 externForcesComposition = nullForce;
	vector3 forwardVector;

	double linearVelocity, linearAcceleration;
public:
	static std::list<PhysicsComponentInterface*> external_forces;

public:
	virtual void addExternalForceReference(PhysicsComponentInterface* force) { external_forces.push_back(force); }
	virtual void delete_external_forces();
	virtual void computeExternalForce();
	virtual vector3 getExternalForces() const { return externForcesComposition; }


	virtual vector3 calculateForceComposition(PhysicsComponentInterface* internalForces);
};


