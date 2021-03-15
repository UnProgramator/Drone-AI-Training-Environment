#pragma once

#include <irrlicht.h>
#include <string>

class StaticObject
{
private:
	bool bHasCollision = true;

protected:
	irr::scene::ISceneNode* meshNode = nullptr;

public:
	const std::string name;

public:
	StaticObject() = delete;
	StaticObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df& position, bool bHasCollision = true, std::string name="");
	virtual ~StaticObject();

	bool colideWith(StaticObject* other);
};

