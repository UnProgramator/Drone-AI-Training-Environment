#include "SensorInterface.h"
#include "GraphicsManager.h"
#include "StaticObject.h"
#include "CommunicationInterface.h"
#include "vector"
#include "DefaultSensors.h"
#include <iostream>

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
SensorInterface::SensorInterface(const std::string& name) :
	name{ name }
{
}

DistanceSensor::DistanceSensor(const std::string& sensorMeshPath, const std::string& sensorTexturePath, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range, const std::string& name) :
	SensorInterface(name), maxRange(range)
{
	/*irr::scene::IMeshSceneNode* mesh = getStaticMesh(sensorMeshPath, sensorTexturePath, nullptr, -1, false);
	meshObj = new StaticObject(mesh, position, rotation, false);*/
	meshObj = new StaticObject(sensorMeshPath, sensorTexturePath, position, rotation, scale, false, false, name);

	rangeObj = new StaticObject(getSphere(0.2f), range * irr::core::vector3df(-1.f, 0.f, 0.f), irr::core::vector3df(), false);
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
		distance = (pointOfColision - pos1).getLength() / DronePhysicsManager::coeficient; // corection, for scale 100 and 50 on mesh
	else
		distance = maxRange;

	ci.parse_double(name.c_str(), distance);
}

bool DistanceSensor::link_to(const Drone* parentDrone)
{
	if(parentDrone != nullptr) parentDrone->setChieldMesh(this->meshObj);
	return parentDrone != nullptr;
}

GPS::GPS(const std::string& name) :
	SensorInterface(name), 
	parent{nullptr}
{
}

void GPS::getDetectedValue(DataCoolectorInterface& ci)
{
	std::vector<double> coordinates(2);  
	
	irr::core::vector3df coord = parent->getPosition();

	coordinates[0] = -coord.Z / DronePhysicsManager::coeficient; //consider N as -Z
	coordinates[1] = coord.X / DronePhysicsManager::coeficient; //consider E as X

	ci.parse_double_array(name.c_str(), coordinates);
}

bool GPS::link_to(const Drone* parentDrone)
{
	this->parent = parentDrone;
	return parentDrone != nullptr;
}

Altimeter::Altimeter(const std::string& name):
	SensorInterface(name), 
	parent{nullptr}
{
}

void Altimeter::getDetectedValue(DataCoolectorInterface& ci) {
	ci.parse_double(name.c_str(), parent->getPosition().Y / DronePhysicsManager::coeficient);
}

bool Altimeter::link_to(const Drone* parentDrone)
{
	this->parent = parentDrone;
	return parentDrone != nullptr;
}

Velocimometer::Velocimometer(const std::string& name):
	SensorInterface(name), 
	parentDrone{ nullptr }
{
}

void Velocimometer::getDetectedValue(DataCoolectorInterface& ci) {
	ci.parse_double(name.c_str(), parentDrone->getForwardVelocity() / DronePhysicsManager::coeficient);
}

bool Velocimometer::link_to(const Drone* parentDrone)
{
	this->parentDrone = parentDrone;
	return parentDrone != nullptr;
}

Accelerometer3D::Accelerometer3D(const std::string&  name):
	SensorInterface(name),
	parentDrone{ nullptr }
{
}

void Accelerometer3D::getDetectedValue(DataCoolectorInterface& ci)
{
	std::vector<double> accelerations(3);
	irr::core::vector3df acc = parentDrone->getAccelerations() / DronePhysicsManager::coeficient;
	accelerations[0] = acc.X;
	accelerations[1] = acc.Y;
	accelerations[2] = acc.Z;
	ci.parse_double_array(name.c_str(), accelerations);
}

bool Accelerometer3D::link_to(const Drone* parentDrone)
{
	this->parentDrone = parentDrone;
	return parentDrone != nullptr;
}


Accelerometer::Accelerometer(const std::string& name):
	SensorInterface(name),
	parentDrone{nullptr}
{
}

void Accelerometer::getDetectedValue(DataCoolectorInterface& ci)
{
	ci.parse_double(name.c_str(), parentDrone->getForwardAcceleration() / DronePhysicsManager::coeficient);
}

bool Accelerometer::link_to(const Drone* parentDrone)
{
	this->parentDrone = parentDrone;
	return parentDrone != nullptr;
}
