#include "PhysicsManager.h"

using vector3 = PhysicsManager::vector3;

const vector3 PhysicsManager::nullForce = vector3(NAN, NAN, NAN);
const vector3 PhysicsManager::zeroForce = vector3(0, 0, 0);

PhysicsManager* getDefaultPsysicsManagerInstanciation()
{
    return nullptr;
}

void PhysicsManager::computeExternalForce()
{
    externForcesComposition = zeroForce;
    for (auto* force : external_forces) {
        externForcesComposition += force->getForce();
    }
}

void PhysicsManager::computeInternalForces(double rotationAngle, double forwardCommand, double UpCommand, double deltaTime)
{

}

void PhysicsManager::computeDroneVelocity(double deltaTime)
{
    if (externForcesComposition == nullForce)
        throw std::exception("external forces not calculated priority");
    if (internalForce == nullForce)
        throw std::exception("internal forces not calculated priority");
}

void PhysicsManager::computeNextPosition(vector3 position)
{
}

void PhysicsManager::delete_external_forces()
{
    for (auto* x : external_forces)
        delete x;
}
