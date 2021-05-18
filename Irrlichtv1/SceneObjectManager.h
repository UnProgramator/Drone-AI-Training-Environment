#pragma once
#include "PhysicsManager.h"
class SceneObjectManager
{
private:
	PhysicsManager* phyMgr;

public:
	void getPhysicsManager(PhysicsManager* phyMgr) { this->phyMgr = phyMgr; }
	PhysicsManager* getPhysicsManager() { return phyMgr;  }
	const PhysicsManager* getPhysicsManager() const { return phyMgr; }
};

extern SceneObjectManager* sceneObjMgr;


