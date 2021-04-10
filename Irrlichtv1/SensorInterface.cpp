#include "SensorInterface.h"
#include "GraphicsManager.h"
#include "StaticObject.h"

bool SensorInterface::showRange = false;

DistanceSensor::DistanceSensor(const std::string& sensorMeshPath, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range)
{
	irr::scene::IMeshSceneNode* mesh = getStaticMesh(sensorMeshPath + "", sensorMeshPath + ".png", nullptr, -1, false);
	meshObj = new StaticObject(mesh, position, rotation, false);

	limitPoint = irr::core::vector3df();
	limitPoint.rotateYZBy(rotation.X);
	limitPoint.rotateXZBy(rotation.Y);
	limitPoint *= range;

	rangeObj = new StaticObject(getSphere(), position + limitPoint, irr::core::vector3df(), false);
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

void DistanceSensor::getDetectedValue(void* location, size_t locationSize)
{
	if (locationSize != sizeof(float))
		throw std::exception("Distance sensor get value: pointer to wrong data size detected");
}
