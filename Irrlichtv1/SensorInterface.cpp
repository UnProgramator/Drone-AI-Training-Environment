#include "SensorInterface.h"
#include "GraphicsManager.h"
#include "StaticObject.h"
#include "CommunicationInterface.h"
#include "vector"

static bool bRangeVisibility = false;

static std::list<StaticObject*> visibilityObject;

void SensorInterface::setSensorsRangeVisibility(bool isVisible) {
	bRangeVisibility = isVisible;
	for (StaticObject* obj : visibilityObject) {
		obj->setVisibility(isVisible);
	}
}
void SensorInterface::toggleSensorsRangeVisibility() {
	SensorInterface::setSensorsRangeVisibility(!bRangeVisibility);
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
	if (bRangeVisibility)
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

	ci.parse_double(name, distance);
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

	ci.parse_double_array(name, coordinates);
}

Altimeter::Altimeter(StaticObject* parent, const char* name):
	SensorInterface(name), parent(parent) 
{
}

void Altimeter::getDetectedValue(CommunicationInterface& ci) {
	ci.parse_double(name, parent->getAbsolutePosition().Y);
}