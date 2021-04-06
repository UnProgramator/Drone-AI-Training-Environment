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
	StaticObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df& position = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), bool bHasCollision = true, std::string name="");
	StaticObject(const std::string & meshPath, const std::string& texturePath, const irr::core::vector3df& position = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), bool bHasCollision = true, std::string name="");
	virtual ~StaticObject();

	bool colideWith(StaticObject* other);
};

