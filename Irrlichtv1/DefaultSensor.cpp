#include "SensorInterface.h"
#include "GraphicsManager.h"
#include "StaticObject.h"
#include "CommunicationInterface.h"
#include "vector"
#include "DefaultSensors.h"

bool SensorInterface::bRangeVisibility = false;

std::list<StaticObject*> SensorInterface::visibilityObject;

void SensorInterface::setSensorsRangeVisibility(bool isVisible) {
	SensorInterface::bRangeVisibility = isVisible;
	for (StaticObject* obj : SensorInterface::visibilityObject) {
		obj->setVisibility(isVisible);
	}
}
void SensorInterface::toggleSensorsRangeVisibility() {
	SensorInterface::setSensorsRangeVisibility(!bRangeVisibility);
}

void SensorInterface::addEntityToRangeVisibilityList(StaticObject* objToAdd) {
	SensorInterface::visibilityObject.push_back(objToAdd);
}

SensorInterface::SensorInterface(const char* name) :
	name{ name}
{
}

DistanceSensor::DistanceSensor(const std::string& sensorMeshPath, irr::scene::ISceneNode* parent, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range, const char* name) :
	SensorInterface(name)
{
	irr::scene::IMeshSceneNode* mesh = getStaticMesh(sensorMeshPath + "", sensorMeshPath + ".png", nullptr, -1, false);
	meshObj = new StaticObject(mesh, position, rotation, false);
	meshObj->setParent(parent);

	rangeObj = new StaticObject(getSphere(), range * irr::core::vector3df(1.f, 0.f, 0.f), irr::core::vector3df(), false);
	rangeObj->setParent(mesh);
	if (SensorInterface::getVisibilityStatus())
		rangeObj->setVisibility(true);
}

void DistanceSensor::getDetectedValue(CommunicationInterface& ci)
{
	double distance;

	irr::core::vector3df pos1 = meshObj->getAbsolutePosition();
	irr::core::vector3df pos2 = rangeObj->getAbsolutePosition();

	irr::core::line3df ray(pos1, pos2);

	irr::core::vector3df pointOfColision;
	irr::core::triangle3df colisionTriangle;

	if (colMan->getSceneNodeAndCollisionPointFromRay(ray, pointOfColision, colisionTriangle))
		distance = (pointOfColision - pos1).getLength();
	else
		distance = INFINITY;

	ci.parse_double(name.c_str(), distance);
}

GPS::GPS(StaticObject* parent, const char* name) :
	SensorInterface(name), parent(parent)
{
}

void GPS::getDetectedValue(CommunicationInterface& ci)
{
	std::vector<double> coordinates(2);  
	
	irr::core::vector3df coord = parent->getAbsolutePosition();

	coordinates[0] = -coord.Z; //consider N as -Z
	coordinates[1] = coord.X; //consider E as X

	ci.parse_double_array(name.c_str(), coordinates);
}

Altimeter::Altimeter(StaticObject* parent, const char* name):
	SensorInterface(name), parent(parent) 
{
}

void Altimeter::getDetectedValue(CommunicationInterface& ci) {
	ci.parse_double(name.c_str(), parent->getAbsolutePosition().Y);
}