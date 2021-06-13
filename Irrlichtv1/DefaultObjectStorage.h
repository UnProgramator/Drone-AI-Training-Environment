#pragma once

#include "ObjectFactory.h"
#include "PhysicsManager.h"
#include "JSONParser.h"

class DefaultObjectStorage
{
private:
	DefaultObjectFactory* objf = nullptr;
	Base_JSONParser* json_p = nullptr;
	PhysicsManager* dronePhyMgr = nullptr;

public:

	virtual void check_init_params();

	inline void set_ObjectFactory(DefaultObjectFactory* objf) { if(!this->objf) this->objf = objf; }
	inline DefaultObjectFactory* get_ObjectFactory() { return this->objf; }

	inline void set_JSONParser(Base_JSONParser* json_p) { if (!this->json_p) this->json_p = json_p; }
	inline Base_JSONParser* get_JSONParser() { return this->json_p; }

	inline void set_PhysicsManager(PhysicsManager* dronePhyMgr) { if (!this->dronePhyMgr) this->dronePhyMgr = dronePhyMgr; }
	inline PhysicsManager* get_PhysicsManager() { return this->dronePhyMgr; }

	virtual ~DefaultObjectStorage();
};

extern DefaultObjectStorage *defObjStorage;

