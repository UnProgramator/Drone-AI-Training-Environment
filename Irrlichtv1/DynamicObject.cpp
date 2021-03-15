#include "DynamicObject.h"

DynamicObject::DynamicObject(irr::scene::ISceneNode* meshNode, irr::core::vector3df& position, irr::core::vector3df forwardVector, bool bHasCollision):
	StaticObject(meshNode, position, bHasCollision), forwardVector{ forwardVector }
{
	this->meshNode->setRotation(forwardVector);
}

DynamicObject::~DynamicObject()
{}

const irr::core::vector3df& DynamicObject::getPosition() const
{
	return this->meshNode->getPosition();
}

void DynamicObject::setPosition(irr::core::vector3df& newPosition)
{
	this->meshNode->setPosition(newPosition);
}
 
const irr::core::vector3df& DynamicObject::getForwardVector() const 
{
	return this->forwardVector;
}

void DynamicObject::addInputVector(irr::core::vector3df& inputVector)
{
	this->meshNode->setPosition(this->meshNode->getPosition() + inputVector);
}

const irr::core::vector3df& DynamicObject::getRotation() const
{
	return this->meshNode->getRotation();
}

void DynamicObject::setRotation(irr::core::vector3df& newRotation)
{
	this->meshNode->setRotation(newRotation);
	this->forwardVector.rotationToDirection(newRotation);
//#pragma warning()
//#pragma message("\t\t\t\tWARNING:   DynamicObject::setRotation need to be finished")
}
