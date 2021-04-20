#include "Drone.h"

#include <irrlicht.h>
#include <iostream>
#include <list>
#include <memory>
#include <Python.h>
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
    this->sensor_list.push_back(sensor);
}

std::list<float> Drone::getDistanceSensorValues()
{
    std::list<float> distance_list;
    float distance=0;
    for (auto* sensor : sensor_list) {
        sensor->getDetectedValue();
        distance_list.push_back(distance);
    }
    return distance_list;
}

PyObject* Drone::getSensorReadValues()
{
    PyObject* retVal = PyList_New(this->sensor_list.size());
    PyObject *pair;
    int crtPosition = 0;
    int except;

    if (retVal == nullptr)
        throw std::exception("Python list object could not be created");

    for (auto* sensor : sensor_list) {
        pair = PyTuple_New(2);
        except = 0;
        if (pair == nullptr)
            throw std::exception("Python list object could not be created");
        except += PyTuple_SetItem(pair, 0, sensor->getName());
        except += PyTuple_SetItem(pair, 1, sensor->getDetectedValue());
        except += PyList_SetItem(retVal, crtPosition, pair);
        if(except != 0)
            throw std::exception("Python PyList_SetItem or PyTuple_SetItem returned -1");
        crtPosition++;
    }

    return retVal;
}

irr::scene::ISceneNode* Drone::getParent()
{
    return mesh->getParent();
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