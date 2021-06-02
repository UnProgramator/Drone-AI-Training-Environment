#include "DefaultPhysicsComponents.h"
#include "PhysicsManager.h"
#include "DefaultObjectStorage.h"

using vector3=PhysicsComponentInterface::vector3;

const vector3& Wind::getForce() const
{
    return force;
}

Wind::Wind()
{
    makeRandom();
}

void Wind::makeRandom()
{
}

void Wind::setForce(const vector3& newForce)
{
    force = newForce;
}

bool DronePhysicsManager::computeForcesResultante(bool bExistExternalForces)
{
    vector3 foceComposition = desiredForce;
    if (bExistExternalForces) // if i don't want to consider external forces (by default i do), the value remains =desiredForce, else i compute the resultante
        foceComposition = defObjStorage->get_PhysicsManager()->calculateForceComposition(this);



    return false;
}

const vector3& DronePhysicsManager::getForce() const
{
    return desiredForce;
}

const vector3& DronePhysicsManager::getVelocity() const
{
    // TODO: insert return statement here
}

const vector3& DronePhysicsManager::getAcceleration() const
{
    // TODO: insert return statement here
}
