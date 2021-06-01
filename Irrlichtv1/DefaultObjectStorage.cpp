#include "DefaultObjectStorage.h"

DefaultObjectStorage *defObjStorage = nullptr;

void DefaultObjectStorage::check_init_params()
{
    if (objf == nullptr)
        objf = new DefaultObjectFactory();
    if (json_p == nullptr)
        json_p = new Base_JSONParser(objf);
    if (dronePhyMgr == nullptr)
        dronePhyMgr = new PhysicsManager();



    if (!(objf || json_p || dronePhyMgr))
        throw new std::exception("DefaultObjectStorage initialization error");
}

DefaultObjectStorage::~DefaultObjectStorage() {
    delete objf;
    delete json_p;
}