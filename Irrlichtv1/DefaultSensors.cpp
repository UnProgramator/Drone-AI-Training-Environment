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

DistanceSensor::DistanceSensor(const std::string& sensorMeshPath, const std::string& sensorTexturePath, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range, const char* name) :
	SensorInterface(name)
{
	/*irr::scene::IMeshSceneNode* mesh = getStaticMesh(sensorMeshPath, sensorTexturePath, nullptr, -1, false);
	meshObj = new StaticObject(mesh, position, rotation, false);*/
	meshObj = new StaticObject(sensorMeshPath, sensorTexturePath, position, rotation, scale, false, false, name);

	rangeObj = new StaticObject(getSphere(), range * irr::core::vector3df(1.f, 0.f, 0.f), irr::core::vector3df(), false);
	rangeObj->setParent(meshObj);
	SensorInterface::addEntityToRangeVisibilityList(rangeObj);
	if (SensorInterface::getVisibilityStatus())
		rangeObj->setVisibility(true);
}

void DistanceSensor::getDetectedValue(DataCoolectorInterface& ci)
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

bool DistanceSensor::link_to(const StaticObject* objectToLinkTo)
{
	meshObj->setParent(objectToLinkTo);
	return false;
}

GPS::GPS(const char* name) :
	SensorInterface(name), 
	parent{nullptr}
{
}

void GPS::getDetectedValue(DataCoolectorInterface& ci)
{
	std::vector<double> coordinates(2);  
	
	irr::core::vector3df coord = parent->getAbsolutePosition();

	coordinates[0] = -coord.Z; //consider N as -Z
	coordinates[1] = coord.X; //consider E as X

	ci.parse_double_array(name.c_str(), coordinates);
}

bool GPS::link_to(const StaticObject* objectToLinkTo)
{
	parent = objectToLinkTo;
	return objectToLinkTo != nullptr;
}

Altimeter::Altimeter(const char* name):
	SensorInterface(name), 
	parent{nullptr}
{
}

void Altimeter::getDetectedValue(DataCoolectorInterface& ci) {
	ci.parse_double(name.c_str(), parent->getAbsolutePosition().Y);
}

bool Altimeter::link_to(const StaticObject* objectToLinkTo)
{
	parent = objectToLinkTo;
	return objectToLinkTo != nullptr;
}

Velocimometer::Velocimometer(const char* name): 
	SensorInterface(name), 
	parentDrone{ nullptr }, parent{ nullptr }
{
}

void Velocimometer::getDetectedValue(DataCoolectorInterface& ci) {
	ci.parse_double(name.c_str(), parentDrone->getForwardVelocity());
}

bool Velocimometer::link_to(const StaticObject* objectToLinkTo) {
	parent = objectToLinkTo;
	return objectToLinkTo != nullptr;
}

void Velocimometer::link_to(const Drone* parentDrone)
{
	this->parentDrone = parentDrone;
}

Accelerometer3D::Accelerometer3D(const char* name):
	SensorInterface(name),
	parentDrone{ nullptr }, parent{ nullptr }
{
}

void Accelerometer3D::getDetectedValue(DataCoolectorInterface& ci)
{
	std::vector<double> accelerations(3);
	irr::core::vector3df acc = parentDrone->getAccelerations();
	accelerations.push_back(acc.Z); //forward
	accelerations.push_back(acc.X); //sideways
	accelerations.push_back(acc.Y); //upwards
	ci.parse_double_array(name.c_str(), accelerations);
}

bool Accelerometer3D::link_to(const StaticObject* objectToLinkTo)
{
	parent = objectToLinkTo;
	return objectToLinkTo != nullptr;
}

void Accelerometer3D::link_to(const Drone* parentDrone)
{
	this->parentDrone = parentDrone;
}

Accelerometer::Accelerometer(const char* name):
	SensorInterface(name),
	parentDrone{nullptr}, parent{ nullptr }
{
}

void Accelerometer::getDetectedValue(DataCoolectorInterface& ci)
{
	ci.parse_double(name.c_str(), parentDrone->getForwardAcceleration());
}

bool Accelerometer::link_to(const StaticObject* objectToLinkTo)
{
	parent = objectToLinkTo;
	return objectToLinkTo != nullptr;
}

void Accelerometer::link_to(const Drone* parentDrone)
{
	this->parentDrone = parentDrone;
}
