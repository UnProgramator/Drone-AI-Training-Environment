#pragma once
#include "StaticObject.h"

#include <irrlicht.h>

class DynamicObject : public StaticObject
{
protected:
	irr::core::vector3df forwardVector;
	irr::core::vector3df rightVector;
public:
	DynamicObject() = delete;
	DynamicObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df & position, const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& forwardVector = irr::core::vector3df(1.f, 0.f, 0.f), bool bHasCollision = true, const std::string name = "");
	DynamicObject(const std::string& meshPath, const std::string& texturePath, const irr::core::vector3df & position, const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& forwardVector = irr::core::vector3df(1.f, 0.f, 0.f), bool bHasCollision = true, const std::string name = "");
	virtual ~DynamicObject();

	virtual const irr::core::vector3df& getForwardVector() const;
	virtual void addInputVector(const irr::core::vector3df & inputVector);
	virtual void moveForward(float distance);
	virtual void moveRight(float distance);

	virtual void setRotation(const irr::core::vector3df & newRotation);

	virtual void rotate(const irr::core::vector3df & angles);
};

