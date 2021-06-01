#include "PhysicsManager.h"

using vector3 = PhysicsManager::vector3;

const vector3 PhysicsManager::nullForce = vector3(NAN, NAN, NAN);
const vector3 PhysicsManager::zeroForce = vector3(0, 0, 0);

void PhysicsManager::computeExternalForce()
{
    externForcesComposition = zeroForce;
    for (auto* force : external_forces) {
        externForcesComposition += force->getForce();
    }
}

vector3 PhysicsManager::calculateForceComposition(PhysicsComponentInterface* internalForces)
{
    computeExternalForce();
    vector3 rezultante = internalForces->getForce() + this->externForcesComposition;
    return rezultante;
}

void PhysicsManager::delete_external_forces()
{
    for (auto* x : external_forces)
        delete x;
}
