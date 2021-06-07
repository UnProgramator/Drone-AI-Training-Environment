#include "Drone.h"

#include <irrlicht.h>
#include <iostream>
#include <list>
#include <memory>
#include "GraphicsManager.h"
#include "DynamicObject.h"
#include "DefaultPhysicsComponents.h"

using namespace std;
using DroneAttributes = Drone::DroneAttributes;
#ifdef drone_debug_on
#error
#endif

#define drone_debug_on true

#if drone_debug_on == true
#define debug_call(x) {std::cerr << x; throw std::exception(x);}
#define debug_call_cond(cond, x) if((cond)) std::cerr << x
#else
#define debug_call(...)
#define debug_call_cond(...)
#endif

Drone::Drone(const irr::core::vector3df& initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df& initalOrientation, const DroneAttributes& atributes):
        atributes{atributes}, las_given_comand{{}}
{
    std::cout << "default drone cube should not be used in final apps";
    irr::scene::IMeshSceneNode* node = getCube(10.f, -1, false);
    mesh= new DynamicObject(node, initalPosition, initalRotation, initalOrientation, true);

    dronePhyMgr = new DronePhysicsManager(mesh->getForwardVector(), atributes);
}

Drone::Drone(const std::string& meshPath, const std::string& textPath, const irr::core::vector3df& initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df& initalOrientation, 
        const DroneAttributes& atributes):
    Drone(meshPath, textPath, initalPosition, initalRotation, irr::core::vector3df(1.f, 1.f, 1.f), initalOrientation, atributes)
{
}

Drone::Drone(const std::string& meshPath, const std::string& textPath, const irr::core::vector3df& initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df& scale, const irr::core::vector3df& initalOrientation, 
        const DroneAttributes& atributes) :
    atributes{ atributes }, las_given_comand{ {} }
{
    mesh = new DynamicObject(meshPath, textPath, initalPosition, initalRotation, initalOrientation, scale, true, false, "Drone");
    dronePhyMgr = new DronePhysicsManager(mesh->getForwardVector(), atributes);
}
Drone::~Drone()
{
    delete mesh;
    for (auto* x : sensor_list)
        delete x;
}


bool Drone::verifyCollision(class StaticObject* otherObject)
{
    return this->mesh->colideWith(otherObject);
}

int Drone::getSensorsNumberOfOutputValues()
{
    int values = 0;
    for (auto x : sensor_list)
        values += x->getNumberOfOutputValues();
    return values;
}

bool Drone::setChieldMesh(StaticObject* child) const
{
    if (child) 
        child->setParent(this->mesh);
    return child != nullptr;
}

void Drone::add_sensor(SensorInterface* sensor)
{
    sensor->link_to(this);
    this->sensor_list.push_back(sensor);
}

void Drone::getSensorReadValues(DataCoolectorInterface& transmiter)
{
    for (auto* sensor : sensor_list) {
        sensor->getDetectedValue(transmiter);
    }
}

bool Drone::giveCommands(default_ReturnedValueFromStript& values)
{
    las_given_comand = values;
    bool good_imput = true;

    if (las_given_comand.up > 1) {
        las_given_comand.up = 1;
        good_imput = false;
    }
    else if (las_given_comand.up < -1) {
        las_given_comand.up = -1;
        good_imput = false;
    }
    
    if (las_given_comand.forward > 1) {
        las_given_comand.forward = 1;
        good_imput = false;
    }
    else if (las_given_comand.forward < -1) {
        las_given_comand.forward = -1;
        good_imput = false;
    }
    
    if (las_given_comand.rotation_angle > 1) {
        las_given_comand.rotation_angle = 1;
        good_imput = false;
    }
    else if (las_given_comand.rotation_angle < -1) {
        las_given_comand.rotation_angle = -1;
        good_imput = false;
    }

    return good_imput;
}

void Drone::tick(float deltaTime) {
#pragma warning(force not in use)
    dronePhyMgr->computeNewParameters(las_given_comand, deltaTime, false); 
    const PhysicsManager::vector3& velocity = dronePhyMgr->getVelocity();

    mesh->addInputVector(velocity * deltaTime);
    mesh->rotate(irr::core::vector3df(0, 1, 0) * las_given_comand.rotation_angle * maxRightRotationSpeed * deltaTime);
}

void Drone::reset(bool toDefault)
{
    this->mesh->reset(toDefault);
    las_given_comand = {};
}

irr::core::vector3df Drone::getVelocity() const
{
    return dronePhyMgr->getVelocity();
}

float Drone::getForwardVelocity() const
{
    return dronePhyMgr->getVelocity().Z;
}

irr::core::vector3df Drone::getAccelerations() const
{
    return dronePhyMgr->getAcceleration();
}

float Drone::getForwardAcceleration() const
{
    return  dronePhyMgr->getAcceleration().Z;
}


void Drone::no_physics_tick(float deltaTime)
{
    /* old implementation that do not use physics*/
    if (las_given_comand.forward != 0 || las_given_comand.up != 0) {

        irr::core::vector3df speed = mesh->getForwardVector();
        if (las_given_comand.forward != 0)
            speed *= las_given_comand.forward * maxFrowardSpeed;
        if (las_given_comand.up != 0)
            speed.Z = las_given_comand.up * maxUpSpeed;
        mesh->addInputVector(speed * deltaTime);
        las_given_comand.forward = las_given_comand.up = 0;
    }
    if (las_given_comand.rotation_angle != 0) {
        mesh->rotate(irr::core::vector3df(0.f, 1.f, 0.f) * las_given_comand.rotation_angle * maxRightRotationSpeed * deltaTime);
        las_given_comand.rotation_angle = 0;
    }
}

#undef drone_debug_on
#undef debug_call_cond