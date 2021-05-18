#include "ObjectFactory.h"

#include <string>
#include <nlohmann/json.hpp>
#include <irrlicht.h>

#include "DefaultSensors.h"
#include "SceneObjectManager.h"

using std::operator""s;
using Json = DefaultObjectFactory::Json;

using vector3 = irr::core::vector3df;

SensorInterface* DefaultObjectFactory::getSensor(std::string& name, Json& atributes)
{
    SensorInterface* sensor = nullptr;
    std::string type = atributes["type"].get<std::string>();

    if (type == "sensor-DistanceSensor-default") {
        std::string mesh = atributes["mesh"].get <std::string>();
        std::string text = atributes["texture"].get <std::string>();
        vector3 postion(atributes["position"][0].get<float>(), atributes["position"][1].get<float>(), atributes["position"][2].get<float>());
        vector3 rotation(atributes["rotation"][0].get<float>(), atributes["rotation"][1].get<float>(), atributes["rotation"][2].get<float>());
        vector3 scale(atributes["scale"][0].get<float>(), atributes["scale"][1].get<float>(), atributes["scale"][2].get<float>());
        float range = atributes["range"].get<float>();
        sensor = new DistanceSensor(mesh, text, postion, rotation, scale, range, name);
    }

    return sensor;
}

Drone* DefaultObjectFactory::getDrone(Json& atributes)
{
    std::string mesh = atributes["mesh"].get<std::string>();
    std::string text = atributes["mesh"].get<std::string>();
    vector3 pos(atributes["mesh-location"][0].get<float>(), atributes["mesh-location"][1].get<float>(),  atributes["mesh-location"][2].get<float>());
    vector3 rot(atributes["mesh-rotation"][0].get<float>(), atributes["mesh-rotation"][1].get<float>(),  atributes["mesh-rotation"][2].get<float>());
    vector3 sca(atributes["mesh-scale"][0].get<float>(),    atributes["mesh-scale"][1].get<float>(),     atributes["mesh-scale"][2].get<float>());
    vector3 forward(atributes["drone-forward"][0].get<float>(), atributes["drone-forward"][1].get<float>(), atributes["drone-forward"][2].get<float>());
    Drone::DroneAttributes *atribs = new Drone::DroneAttributes();
    atribs->maxAltitude = atributes["max-altitude"].get<float>();
    atribs->maxForwardAcceleration = atributes["max-forward-acceleration"].get<float>();
    atribs->maxForwardVelocity = atributes["max-forward-velocity"].get<float>();
    atribs->maxUpwardAcceleratio = atributes["max-upward-acceleration"].get<float>();
    atribs->maxUpwardVelocity = atributes["max-upward-velocity"].get<float>();
    
    return new Drone(mesh, text, pos, rot, sca, forward, sceneObjMgr->getPhysicsManager(), atribs);
}

StaticObject* DefaultObjectFactory::getStaticObject(Json& atributes)
{
    return nullptr;
}

DynamicObject* DefaultObjectFactory::getDynamicObject(Json& atributes)
{
    return nullptr;
}

ObjectControllerInterface* DefaultObjectFactory::getAI(const std::string& name, Json& atributes)
{
    return nullptr;
}
