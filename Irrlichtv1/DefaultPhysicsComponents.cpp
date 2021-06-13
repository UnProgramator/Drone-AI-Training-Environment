#include "DefaultPhysicsComponents.h"
#include "PhysicsManager.h"
#include "DefaultObjectStorage.h"
#include "Drone.h"
#include <irrlicht.h> // pentru vector3df
#define _USE_MATH_DEFINES
#include <math.h>

using vector3=PhysicsComponentInterface::vector3;

const float DronePhysicsManager::coeficient = 5000.f;

const vector3& Wind::getForce() const
{
    return force;
}

Wind::Wind(const vector3& direction, const float velocity) {
    if (direction.getLength() != 0)
        force = compute_force(direction / direction.getLength(), velocity); // fst arg is making shure that the vector modulus is 1
    else
        force = PhysicsManager::zeroForce;
}

Wind::Wind()
{
    makeRandom();
}

void Wind::makeRandom()
{
    vector3 direction = vector3(rand() % 100, rand() % 100, rand() % 100); // make random vector
    while(direction == PhysicsManager::zeroForce)
        direction = vector3(rand() % 100, rand() % 100, rand() % 100); // if force is 0 then i repeat
    direction /= direction.getLength(); // make vector unit vector

    float velocity = (rand() % 9750) / 150.0 + 5.0; // the velocity will have a value between 5km/h and ~70km/h

    this->force = compute_force(direction, velocity);
}

void Wind::setForce(const vector3& direction, float velocity)
{
    force = compute_force(direction / direction.getLength(), velocity);
}

vector3 Wind::compute_force(const vector3& direction, float velocity)
{
    /* formula from https://sciencing.com/convert-wind-speed-force-5985528.html
    * the formula i use to calculate the wind force is
    * F = m*a = area * air_density * wind-velocity
    * are is area of impact
    * for simplicity i will consider the area as
    */
    float forceModulus = 1.229 * velocity * velocity;
    return direction * forceModulus;
}

void Wind::verify_direction(vector3& vec) // verify and validate the wind direction; make corections if needed
{
    if(abs(acos(vec.dotProduct(vector3(0, 1, 0)) > M_PI_4))) { // if make a angle to big towards Y or -Y, than make angle smaller
        vec.Y /= 4;
    }
}

DronePhysicsManager::DronePhysicsManager(const vector3& forwardsDirection, const DroneAttributes& attrs):
    forwardsDirection{ forwardsDirection }, mass{ attrs.mass}, //forward vector ref, mass value
    maxUpVelocity{ coeficient* attrs.maxUpwardVelocity * (10.f / 36) },
    maxDownVelocity{ coeficient* attrs.maxDownwordsVelocity * (10.f / 36) },
    maxPlaneVelocity{ coeficient* attrs.maxForwardVelocity * (10.f / 36) }, //maximum linear velocity for orientation
    /** from a = dv/dt
    *   maxAccelerationInKPH(km/h)/maxAccelerationTimeInSeconds(s)
    *   -> (maxAccelerationInKPH * 10^3/3600 (m/s))/(maxAccelerationTimeInSeconds)
    *   -> maxAccelerationInKPH * (10/36/maxAccelerationTimeInSeconds)
    *   -> maxAccelerationInKPH/maxAccelerationTimeInSeconds * (10/36)
    *   from formula acceleration = delta(velocity)/time-of-acceleration
    *   for simplification i use the simplified linear acceleration formula
    * */
    maxLinearAcceleration{ coeficient * attrs.maxAccelerationInKPH / attrs.maxAccelerationTimeInSeconds * (10.f / 36) },
    phyMgr{ defObjStorage->get_PhysicsManager() }
{
}

bool DronePhysicsManager::computeNewParameters(const default_ReturnedValueFromStript& inputs, float deltaTime, bool bExistExternalForces)
{
    //here I compute internal acceleration on next frame
    vector3 new_acc = crt3DAcceleration + forwardsDirection * inputs.forward * maxLinearAcceleration *deltaTime + vector3(0, 1, 0) * inputs.up * maxLinearAcceleration * deltaTime;

    acceleration_corection(new_acc, inputs, deltaTime);

    if (new_acc.getLength() > maxLinearAcceleration) { // cap acceleration to maximum acceleration
        new_acc *= (maxLinearAcceleration / new_acc.getLength());
    }

    //velocity calculated base on internal foces, uncaped to the drone max velocity
    vector3 new_vel = crt3DVelocity + new_acc * 2 * deltaTime; // acceleration calculated for times from last call, given throw deltaTime., delta time is given in seconds // the 2 coef will be removed in future

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

    acceleration_corection(new_acc, inputs, deltaTime);

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
    crt3DVelocity = new_vel;

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

void DronePhysicsManager::reset()
{
    crt3DAcceleration = PhysicsManager::zeroForce;
    crt3DVelocity = PhysicsManager::zeroForce;
}

// function apply inertia, friction and gravoty effects to acceleration for more acurate values
// function will consider the new acceleration (based only on internal forces and prevoiuse acceleration,
// the current velocity and the inputs
void DronePhysicsManager::acceleration_corection(vector3& acceleration, const default_ReturnedValueFromStript& inputs, float deltatime)
{
    if (inputs.forward == 0) {
        acceleration.X = 0; // acceleration descend directly to 0
        acceleration.Z = 0;

        
    }
    if (inputs.up == 0) {
        acceleration.Y = 0; // acceleration descend directly to 0
        crt3DVelocity.Y *= 1 / 3; // velocity go down because of friction 
    }
    float yval = crt3DVelocity.Y; // velocity go down because of friction
    crt3DVelocity *= (1 / 6) * deltatime;// velocity direction corection for now
    crt3DVelocity.Y = yval;
}
