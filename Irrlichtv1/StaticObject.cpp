#include "StaticObject.h"

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
	return this->meshNode->getTransformedBoundingBox().intersectsWithBox(other->meshNode->getTransformedBoundingBox());
}

StaticObject::StaticObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df& position, bool bHasCollision, std::string name): name(name)
{
	this->meshNode = meshNode;
	this->meshNode->setPosition(position);
	if (bHasCollision && !meshNode->getTriangleSelector())
		throw std::exception("No triangle selector found for mesh marked for colision");
}
