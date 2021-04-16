#include "SensorInterface.h"
#include "GraphicsManager.h"
#include "StaticObject.h"

bool SensorInterface::showRange = false;

DistanceSensor::DistanceSensor(const std::string& sensorMeshPath, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range)
{
	irr::scene::IMeshSceneNode* mesh = getStaticMesh(sensorMeshPath + "", sensorMeshPath + ".png", nullptr, -1, false);
	meshObj = new StaticObject(mesh, position, rotation, false);


	rangeObj = new StaticObject(getSphere(), range * irr::core::vector3df(1.f, 0.f, 0.f), irr::core::vector3df(), false);
	rangeObj->setParent(mesh);
	if (showRange)
		rangeObj->setVisibility(true);
}

void DistanceSensor::setParent(irr::scene::ISceneNode* parent)
{
	meshObj->setParent(parent);
}

void DistanceSensor::setPosition(const irr::core::vector3df& positon)
{
}

void setPosition(const irr::core::vector3df& positon) 
{
}

void DistanceSensor::setOrientation(const irr::core::vector3df& orientation)
{
}

PyObject* DistanceSensor::getDetectedValue()
{
	PyObject* retVal = nullptr;



	return nullptr;
}
