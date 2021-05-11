#include "DynamicObject.h"
#include <iostream>

DynamicObject::DynamicObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df & position, const irr::core::vector3df& rotation, const irr::core::vector3df& forwardVector, bool bHasCollision, const std::string name):
	StaticObject(meshNode, position, rotation, bHasCollision, name), forwardVector{ forwardVector/forwardVector.getLength() }
{
	rightVector = forwardVector;
	rightVector.rotateXZBy(90);
}

DynamicObject::DynamicObject(const std::string& meshPath, const std::string& texturePath, const irr::core::vector3df& position, const irr::core::vector3df& rotation, const irr::core::vector3df& forwardVector, bool bHasCollision, const std::string name):
	StaticObject(meshPath, texturePath, position, rotation, bHasCollision, name), forwardVector{ forwardVector / forwardVector.getLength() }
{
	rightVector = forwardVector;
	rightVector.rotateXZBy(90);
}

DynamicObject::~DynamicObject()
{}
 
const irr::core::vector3df& DynamicObject::getForwardVector() const 
{
	return this->forwardVector;
}

void DynamicObject::addInputVector(const irr::core::vector3df & inputVector)
{
	this->meshNode->setPosition(this->meshNode->getPosition() + inputVector);
}

void DynamicObject::moveForward(float distance)
{
	setPosition(getPosition() + distance * forwardVector);
}

void DynamicObject::moveRight(float distance)
{
	setPosition(getPosition() + distance * rightVector);
}


void DynamicObject::setRotation(const irr::core::vector3df & newRotation)
{
	StaticObject::setRotation(newRotation);
	this->forwardVector = this->forwardVector.rotationToDirection(newRotation);
	rightVector = forwardVector;
	rightVector.rotateXZBy(90);
}

void DynamicObject::rotate(const irr::core::vector3df & angles)
{
	irr::core::vector3df rot = this->meshNode->getRotation();

	rot += angles;

	this->StaticObject::setRotation(rot);

	this->forwardVector.rotateXYBy(-angles.Z);
	this->forwardVector.rotateXZBy(-angles.Y);
	this->forwardVector.rotateYZBy(-angles.X);
	this->rightVector.rotateXYBy(-angles.Z);
	this->rightVector.rotateXZBy(-angles.Y);
	this->rightVector.rotateYZBy(-angles.X);
}
