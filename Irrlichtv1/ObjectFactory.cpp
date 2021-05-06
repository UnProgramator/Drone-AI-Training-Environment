#include "ObjectFactory.h"

#include <string>

using std::operator""s;

SensorInterface* DefaultObjectFactory::getSensor(std::string& name)
{
    SensorInterface* sensor = nullptr;

    if (name == "distance sensor") {
        //sensor = DistanceSensor();
    }

    return sensor;
}

Drone* DefaultObjectFactory::getDrone()
{
    return nullptr;
}

StaticObject* DefaultObjectFactory::getStaticObject()
{
    return nullptr;
}

DynamicObject* DefaultObjectFactory::getDynamicObject()
{
    return nullptr;
}

ObjectControllerInterface* DefaultObjectFactory::getAI(const std::string& name)
{
    return nullptr;
}
