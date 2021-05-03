#pragma once

#include <irrlicht.h>

class PhysicsComponentInterface
{
public:
	virtual irr::core::vector3df getForce() =0;
};

