#include "DynamicObject.h"

DynamicObject::DynamicObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df & position, const irr::core::vector3df& rotation, const irr::core::vector3df& forwardVector, bool bHasCollision, const std::string name):
	StaticObject(meshNode, position, rotation, bHasCollision, name), forwardVector{ forwardVector/forwardVector.getLength() }
{
}

DynamicObject::DynamicObject(const std::string& meshPath, const std::string& texturePath, const irr::core::vector3df& position, const irr::core::vector3df& rotation, const irr::core::vector3df& forwardVector, bool bHasCollision, const std::string name):
	StaticObject(meshPath, texturePath, position, rotation, bHasCollision, name), forwardVector{ forwardVector / forwardVector.getLength() }
{
}

DynamicObject::~DynamicObject()
{}

const irr::core::vector3df& DynamicObject::getPosition() const
{
	return this->meshNode->getPosition();
}

void DynamicObject::setPosition(const irr::core::vector3df & newPosition)
{
	this->meshNode->setPosition(newPosition);
}
 
const irr::core::vector3df& DynamicObject::getForwardVector() const 
{
	return this->forwardVector;
}

void DynamicObject::addInputVector(const irr::core::vector3df & inputVector)
{
	this->meshNode->setPosition(this->meshNode->getPosition() + inputVector);
}

const irr::core::vector3df& DynamicObject::getRotation() const
{
	return this->meshNode->getRotation();
}

void DynamicObject::setRotation(const irr::core::vector3df & newRotation)
{
	this->meshNode->setRotation(newRotation);
	this->forwardVector.rotationToDirection(newRotation);
//#pragma warning()
//#pragma message("\t\t\t\tWARNING:   DynamicObject::setRotation need to be finished")
}

void DynamicObject::rotate(const irr::core::vector3df & angles)
{
	irr::core::vector3df rot = this->meshNode->getRotation();

	rot += angles;

	this->meshNode->setRotation(rot);
}
