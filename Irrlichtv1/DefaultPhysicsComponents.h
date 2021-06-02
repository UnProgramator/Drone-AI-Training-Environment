#pragma once
#include "PhysicsComponentInterface.h"


class Wind : public PhysicsComponentInterface {
	vector3 force;
public:
	using vector3 = PhysicsComponentInterface::vector3;
	virtual const vector3& getForce() const override;
	Wind();
	void makeRandom();
	void setForce(const vector3&);
};

class DronePhysicsManager : public PhysicsComponentInterface {
	using vector3 = PhysicsComponentInterface::vector3;
	vector3 desiredForce;
public:
	virtual bool computeForcesResultante(bool bExistExternalForces);


	virtual const vector3& getForce() const override;
	virtual const vector3&  getVelocity() const;
	virtual const vector3&  getAcceleration() const;
};