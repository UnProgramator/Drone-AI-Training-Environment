#pragma once

#include <irrlicht.h>

class PhysicsComponentInterface
{
public:
	using vector3 = irr::core::vector3df;

	virtual vector3& getForce() const =0;
};

