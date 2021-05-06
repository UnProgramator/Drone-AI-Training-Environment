#include "StaticObject.h"
#include "GraphicsManager.h"
#include <iostream>
#include <list>

std::list<StaticObject*> StaticObject::createdObjects;

StaticObject::~StaticObject()
{
	if (meshNode) {
		meshNode->drop();
		meshNode->remove();
		// tbd
	}
}

bool StaticObject::colideWith(StaticObject* other)
{
	if (!this->bHasCollision || !other->bHasCollision)
		return false;
	return this->meshNode->getTransformedBoundingBox().intersectsWithBox(other->meshNode->getTransformedBoundingBox());
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

StaticObject::StaticObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df& position, const irr::core::vector3df& rotation, bool bHasCollision, std::string name): name(name)
{
	this->meshNode = meshNode;
	this->meshNode->setPosition(position);
	this->meshNode->setRotation(rotation);
	StaticObject::createdObjects.push_back(this);
}

StaticObject::StaticObject(const std::string & meshPath, const std::string& texturePath, const irr::core::vector3df& position, const irr::core::vector3df& rotation, bool bHasCollision, std::string name) : name(name)
{
	this->meshNode = getStaticMesh(meshPath, texturePath, nullptr, -1, bHasCollision);
	this->meshNode->setPosition(position);
	this->meshNode->setRotation(rotation);
	StaticObject::createdObjects.push_back(this);
}
