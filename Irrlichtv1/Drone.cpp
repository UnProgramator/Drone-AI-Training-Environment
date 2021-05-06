#include "Drone.h"

#include <irrlicht.h>
#include <iostream>
#include <list>
#include <memory>
#include "DynamicObject.h"
#include "GraphicsManager.h"

using namespace std;

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

Drone::Drone(const irr::core::vector3df& initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df& initalOrientation)
{
    std::cout << "drone created";
    irr::scene::IMeshSceneNode* node = getCube();
    mesh= new DynamicObject(node, initalPosition, initalRotation, initalOrientation, true);
}

Drone::Drone(const std::string& path, const irr::core::vector3df& initalPosition, const irr::core::vector3df& initalRotation, const irr::core::vector3df& initalOrientation)
{
    irr::scene::IMeshSceneNode* node = getStaticMesh(path + "", path + ".png", 0);
    mesh = new DynamicObject(node, initalPosition, initalRotation, initalOrientation, true);
} 

bool Drone::verifyCollision(class StaticObject* otherObject)
{
    return this->mesh->colideWith(otherObject);
}

void Drone::moveForwards(float ratio)
{
    if (ratio > 1.f) {
        debug_call("supraunitary forward movement ration detected");
        ratio = 1.f;
    }
    else if (ratio < -1.f) {
        debug_call("supraunitary forward negative ration movement detected");
        ratio = -1.f;
    }

    debug_call_cond(ratio<=0, "negative forward movement detected");

    forward_ratio = ratio;
}

void Drone::rotateRight(float ratio)
{
    if (ratio > 1.f) {
        debug_call("supraunitary right turm movement ratio detected");
        ratio = 1.f;
    }
    else if (ratio < -1.f) {
        debug_call("supraunitary right negative turm movement ratio detected");
        ratio = -1.f;
    }

    rotation_ratio = ratio;
}

void Drone::moveUp(float ratio)
{
    if (ratio > 1.f) {
        debug_call("supraunitary forward movement ration detected");
        ratio = 1.f;
    }
    else if (ratio < -1.f) {
        debug_call("supraunitary forward negative ration movement detected");
        ratio = -1.f;
    }

    up_ratio = ratio;
}

void Drone::add_sensor(DistanceSensor* sensor)
{
    sensor->link_to(this->mesh);
    this->sensor_list.push_back(sensor);
}

void Drone::getSensorReadValues(default_CommunicationInterface& transmiter)
{
    transmiter.init_parser(sensor_list.size());
    for (auto* sensor : sensor_list) {
        sensor->getDetectedValue(transmiter);
    }
}

void Drone::tick()
{
    if (forward_ratio != 0 || up_ratio != 0) {

        irr::core::vector3df vec = mesh->getForwardVector();
        if (forward_ratio != 0)
            vec *= forward_ratio * maxFrowardSpeed;
        if (up_ratio != 0)
            vec.Z = up_ratio * maxUpSpeed;
        mesh->addInputVector(vec);
        forward_ratio = up_ratio = 0;
    }
    if (rotation_ratio != 0) {
        mesh->rotate(irr::core::vector3df(0.f, 1.f, 0.f) * rotation_ratio * maxRightRotationSpeed);
        rotation_ratio = 0;
    }
}


#undef drone_debug_on
#undef debug_call_cond