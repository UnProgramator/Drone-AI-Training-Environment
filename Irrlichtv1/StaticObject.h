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
	//the defaults values are intialized in contructor, to the values given throw position, rotation, bHasCollision
	const irr::core::vector3df defaultPosition, defaultRotation;
	const bool defaultHasCollision;

public:
	StaticObject() = delete;
	StaticObject(irr::scene::ISceneNode* meshNode, const irr::core::vector3df& position = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), bool bHasCollision = true, std::string name="");
	StaticObject(const std::string & meshPath, const std::string& texturePath, const irr::core::vector3df& position = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& rotation = irr::core::vector3df(0.f, 0.f, 0.f), const irr::core::vector3df& scale = irr::core::vector3df(1.f, 1.f, 1.f), bool bHasCollision = true, std::string name="");
	virtual ~StaticObject();

	bool colideWith(StaticObject* other);

	virtual const irr::core::vector3df getAbsolutePosition() const { return this->meshNode->getAbsolutePosition(); }
	virtual const irr::core::vector3df getPosition()		  const { return meshNode->getPosition(); }
	virtual void setPosition(const irr::core::vector3df& newPosition);

	virtual const irr::core::vector3df getRotation() const { return meshNode->getRotation(); }
	virtual void setRotation(const irr::core::vector3df& newRotation);

	const irr::scene::ISceneNode* getRootParent() const;
	const irr::scene::ISceneNode* getSceneNode() const;
	virtual void setParent(irr::scene::ISceneNode* parent) { if (meshNode) meshNode->setParent(parent); else throw std::exception("set parent for unitialized node"); }
	virtual void setParent(const StaticObject* parent) { if (parent && parent->meshNode && meshNode) meshNode->setParent(parent->meshNode); else throw std::exception("set parent for unitialized node or from unitialized node"); }

	virtual void setVisibility(bool isVisible = true) { meshNode->setVisible(isVisible); }
	inline static void setVisibilityForAll(bool isVisible = true) { for (auto* obj : createdObjects)obj->setVisibility(isVisible); }

	virtual void reset(bool toDefaults =true);
};

