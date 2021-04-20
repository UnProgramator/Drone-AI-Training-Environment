#pragma once

#include <irrlicht.h>
#include <string>
#include <list>

class StaticObject
{
private:
	bool bHasCollision = true;

protected:
	irr::scene::ISceneNode* meshNode = nullptr;
	static std::list<StaticObject*> createdObjects;

public:
	const std::string name;

public:
	StaticObject() = delete;
	StaticObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df& position = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), bool bHasCollision = true, std::string name="");
	StaticObject(const std::string & meshPath, const std::string& texturePath, const irr::core::vector3df& position = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), bool bHasCollision = true, std::string name="");
	virtual ~StaticObject();

	inline void setParent(irr::scene::ISceneNode* parent) { if (meshNode) meshNode->setParent(parent); else throw std::exception("set parent for unitialized node"); }
	inline void setParent(StaticObject* parent) { if (parent && parent->meshNode && meshNode) meshNode->setParent(parent->meshNode); else throw std::exception("set parent for unitialized node or from unitialized node"); }
	inline const irr::core::vector3df& getRelativePosition() { return this->meshNode->getPosition(); }
	inline const irr::core::vector3df getAbsolutePosition() { return this->meshNode->getAbsolutePosition(); }

	inline const irr::core::vector3df& getRotation() { return this->meshNode->getRotation(); }

	bool colideWith(StaticObject* other);

	irr::scene::ISceneNode* getParent();

	inline void setVisibility(bool isVisible = true) { meshNode->setVisible(isVisible); }
	inline static void setVisibilityForAll(bool isVisible = true) { for (auto* obj : createdObjects)obj->setVisibility(isVisible); }
};

