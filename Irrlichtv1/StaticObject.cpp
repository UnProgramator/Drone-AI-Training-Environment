#include "StaticObject.h"
#include "GraphicsManager.h"
#include <iostream>
#include <list>

std::list<StaticObject*> StaticObject::createdObjects;

using namespace irr;
using vector3 = core::vector3df;

StaticObject::~StaticObject()
{
	if (meshNode) {
		meshNode->drop();
		meshNode->remove();
		// tbd
	}
}

void StaticObject::reset(bool toDefaults) {
	if (toDefaults) {
		this->meshNode->setPosition(this->defaultPosition);
		this->meshNode->setRotation(this->defaultRotation);
	}
	else {
		vector3 zero_pos;
		this->meshNode->setPosition(zero_pos);
		this->meshNode->setRotation(zero_pos);
	}
}

bool StaticObject::colideWith(StaticObject* other)
{
	if (!this->bHasCollision || !other->bHasCollision)
		return false;
	return this->meshNode->getTransformedBoundingBox().intersectsWithBox(other->meshNode->getTransformedBoundingBox());
}

void StaticObject::setPosition(const irr::core::vector3df& newPosition) {
	this->meshNode->setPosition(newPosition);
}

void StaticObject::setRotation(const irr::core::vector3df& newRotation) {
	this->meshNode->setRotation(newRotation);
}

const irr::scene::ISceneNode* StaticObject::getRootParent() const
{
	irr::scene::ISceneNode *tmp, *par =  meshNode->getParent();
	if (par == 0)
		return meshNode;
	else {
		tmp = par->getParent();
		while (tmp) {
			par = tmp;
			tmp = par->getParent();
		}
	}
	return par;
}

const irr::scene::ISceneNode* StaticObject::getSceneNode() const{
	return this->meshNode;
}

StaticObject::StaticObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df& position, const irr::core::vector3df& rotation, bool bHasCollision, std::string name): 
	name(name), defaultPosition(position), defaultRotation(rotation), defaultHasCollision(bHasCollision)
{
	this->meshNode = meshNode;
	this->meshNode->setPosition(position);
	this->meshNode->setRotation(rotation);
	StaticObject::createdObjects.push_back(this);
}

StaticObject::StaticObject(const std::string & meshPath, const std::string& texturePath, const irr::core::vector3df& position, const irr::core::vector3df& rotation, bool bHasCollision, std::string name) : 
	name(name), defaultPosition(position), defaultRotation(rotation), defaultHasCollision(bHasCollision)
{
	this->meshNode = getStaticMesh(meshPath, texturePath, nullptr, -1, bHasCollision);
	this->meshNode->setPosition(position);
	this->meshNode->setRotation(rotation);
	StaticObject::createdObjects.push_back(this);
}

