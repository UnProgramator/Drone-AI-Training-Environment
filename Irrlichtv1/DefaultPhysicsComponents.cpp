#include "DefaultPhysicsComponents.h"


const PhysicsComponentInterface::vector3& Wind::getForce() const
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

const PhysicsComponentInterface::vector3& DronePhysicsManager::getForce() const
{
    // TODO: insert return statement here
}
