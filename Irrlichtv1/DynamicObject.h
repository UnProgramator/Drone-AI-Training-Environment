#pragma once
#include "StaticObject.h"

#include <irrlicht.h>

class DynamicObject : public StaticObject
{
protected:
	irr::core::vector3df forwardVector;
public:
	DynamicObject() = delete;
	DynamicObject(irr::scene::ISceneNode* meshNode, irr::core::vector3df& position, irr::core::vector3df forwardVector = irr::core::vector3df(1.f, 0.f, 0.f), bool bHasCollision = true);
	virtual ~DynamicObject();

	virtual const irr::core::vector3df& getPosition() const;
	virtual void setPosition(irr::core::vector3df& newPosition);

	virtual const irr::core::vector3df& getForwardVector() const;
	virtual void addInputVector(irr::core::vector3df& inputVector);

	virtual const irr::core::vector3df& getRotation() const;
	virtual void setRotation(irr::core::vector3df& newRotation);
	//virtual void rotate(irr::core::vector3df& angles); //?
	//virtual void rotate(irr::core::quaternion& angles); //?

};

