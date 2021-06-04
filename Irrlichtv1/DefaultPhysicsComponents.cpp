#include "DefaultPhysicsComponents.h"
#include "PhysicsManager.h"
#include "DefaultObjectStorage.h"
#include "Drone.h"
#include <irrlicht.h> // pentru vector3df

using vector3=PhysicsComponentInterface::vector3;

const vector3& Wind::getForce() const
{
    return force;
}

Wind::Wind(const vector3& direction, const float velocity) {
    force = direction / direction.getLength() * velocity;
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

DronePhysicsManager::DronePhysicsManager(const vector3& forwardsDirection, const DroneAttributes& attrs):
    forwardsDirection{ forwardsDirection }, mass{ attrs.mass}, //forward vector ref, mass value
    maxUpVelocity{attrs.maxUpwardVelocity}, maxDownVelocity{ attrs.maxDownwordsVelocity }, maxPlaneVelocity{ attrs.maxForwardVelocity }, //maximum linear velocity for orientation
    /** from a = dv/dt
    *   maxAccelerationInKPH(km/h)/maxAccelerationTimeInSeconds(s)
    *   -> (maxAccelerationInKPH * 10^3/3600 (m/s))/(maxAccelerationTimeInSeconds)
    *   -> maxAccelerationInKPH * (10/36/maxAccelerationTimeInSeconds)
    *   -> maxAccelerationInKPH/maxAccelerationTimeInSeconds * (10/36)
    *   from formula acceleration = delta(velocity)/time-of-acceleration
    *   for simplification i use the simplified linear acceleration formula
    * */
    maxLinearAcceleration{ attrs.maxAccelerationInKPH / attrs.maxAccelerationTimeInSeconds * (10 / 36) },
    linearAccelerationPerCalculation{ maxLinearAcceleration / (attrs.maxAccelerationTimeInSeconds )},
    phyMgr{ defObjStorage->get_PhysicsManager() }
{
}

bool DronePhysicsManager::computeNewParameters(const default_ReturnedValueFromStript& inputs, float deltaTime, bool bExistExternalForces)
{
    //here I compute internal acceleration on next frame
    vector3 new_acc = crt3DAcceleration + forwardsDirection * inputs.forward * linearAccelerationPerCalculation*deltaTime + vector3(0, 1, 0) * inputs.up * linearAccelerationPerCalculation * deltaTime;

    acceleration_corection(new_acc, inputs);

    //velocity calculated base on internal foces, uncaped to the drone max velocity
    vector3 new_vel = crt3DVelocity + new_acc * deltaTime; // acceleration calculated for times from last call, given throw deltaTime., delta time is given in seconds

    //corection for velocity, if acceleration is zero, because of frictional forces => deceleration
    //and this will include (simulate) the inrtia (inertial force)
    //will be aplied before the extrernal forces
    vector3 dest = PhysicsManager::zeroForce;

    if (inputs.forward > 0)
        dest = forwardsDirection * maxPlaneVelocity;
    else
        dest = forwardsDirection * -maxPlaneVelocity;

    if (inputs.up > 0)
        dest.Z = maxUpVelocity;
    else
        dest.Z = maxDownVelocity;

    // if no external force, then this is the final value for velocity
    //max  velocity caption
    float yVal;
    if (new_vel.Y > maxUpVelocity)
        yVal = maxUpVelocity;
    else if (new_vel.Y < -maxDownVelocity)
        yVal = -maxDownVelocity;
    else
        yVal = new_vel.Y;

    //here i compute the linear velocity
    new_vel.Y = 0;
    float planeVelocity = new_vel.getLength();
    if (planeVelocity > maxPlaneVelocity)
        new_vel *= maxPlaneVelocity / planeVelocity; // if linear velocity exced the maximum linear velocity, than cape

    new_vel.Y = yVal; // restore the vertical velocity

    if (bExistExternalForces) { // if i don't want to consider external forces (by default i do), the value remains =desiredForce, else i compute the resultante
        //compute velocity etc
        vector3 ext_force = phyMgr->getExternalForces();
        vector3 external_acc = ext_force / mass * deltaTime; // for it aplies for the times from last call, given throw deltaTime
        //the acceleration induction by internal and external forces

// de vazut daca acceleratia indusa de vant trebuie adunata de fiecare data, ceva imi pare ca nu va merge bine
        new_acc = new_acc + external_acc; // thje force-acceleration composition for both internal and external forces
                                //F_rezultanta = F_intern + F_extern, F = m*a and mass is equal in all forces => a_rez = a_int + a_ext
        new_vel += external_acc * deltaTime; // sam e as before, the accelerantion is calculated for the times from last call, given throw deltaTime
    }

    crt3DAcceleration = new_acc;

    return true;
}

const vector3& DronePhysicsManager::getForce() const
{
    return crt3DAcceleration * mass;
}

const vector3& DronePhysicsManager::getVelocity() const
{
    return crt3DVelocity;
}

const vector3& DronePhysicsManager::getAcceleration() const
{
    return crt3DAcceleration;
}

// function apply inertia, friction and gravoty effects to acceleration for more acurate values
// function will consider the new acceleration (based only on internal forces and prevoiuse acceleration,
// the current velocity and the inputs
void DronePhysicsManager::acceleration_corection(vector3& acceleration, const default_ReturnedValueFromStript& inputs)
{

}
