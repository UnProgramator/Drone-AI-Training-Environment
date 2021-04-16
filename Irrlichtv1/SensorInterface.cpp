#include "SensorInterface.h"
#include "GraphicsManager.h"
#include "StaticObject.h"

bool SensorInterface::showRange = false;

SensorInterface::SensorInterface(const char* name) :
	name{ PyUnicode_FromString(name)}
{
}

DistanceSensor::DistanceSensor(const std::string& sensorMeshPath, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range, const char* name) :
	SensorInterface(name)
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
	double distance;

	irr::core::vector3df pos1 = meshObj->getAbsolutePosition();
	irr::core::vector3df pos2 = rangeObj->getAbsolutePosition();

	irr::core::line3df ray(pos1, pos2);

	irr::core::vector3df pointOfColision;
	irr::core::triangle3df colisionTriangle;
	//irr::scene::ISceneNode* node;

	if (colMan->getSceneNodeAndCollisionPointFromRay(ray, pointOfColision, colisionTriangle))
		distance = (pointOfColision - pos1).getLength();
	else
		distance = INFINITY;

	retVal = PyTuple_New(2);
	PyTuple_SetItem(retVal, 0, this->name);
	PyTuple_SetItem(retVal, 1, PyFloat_FromDouble(distance));

	return retVal;
}


