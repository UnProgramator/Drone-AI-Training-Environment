#include "Drone.h"

#include <irrlicht.h>
#include <iostream>

#include "DynamicObject.h"
#include "GraphicsManager.h"

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
    irr::scene::IMeshSceneNode* node = getCube();
    mesh= new DynamicObject(node, initalPosition, initalRotation, initalOrientation, true);
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

    mesh->addInputVector(mesh->getForwardVector() * maxFrowardSpeed * ratio);
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

    mesh->rotate(irr::core::vector3df(0.f, 0.f, 1.f) * maxRightRotationSpeed * ratio);
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

    mesh->addInputVector(mesh->getForwardVector() * maxUpSpeed * ratio);
}


#undef drone_debug_on
#undef debug_call_cond