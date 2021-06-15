#pragma once
#include "CommunicationInterface.h"
#include <irrlicht.h>
#include "PhysicsManager.h"
#include "Drone.h"

class DebugingStubComunicator:public DataCoolectorInterface, public default_CommunicationInterface
{
	float x=0, y = 0, z = 0, xd = 0, yd = 0, zd = 0;
	irr::core::vector3df lastPosition = PhysicsManager::nullForce;
	Drone *comandedDrone;
	float crt_time, read_time;
	float for_dist = 100000.f;
public:
	DebugingStubComunicator(Drone* obj) :comandedDrone(obj) {}

	virtual void init_parser(int elementCount);
	virtual void parse_double(const char* name, const double value);
	virtual void parse_double_array(const char* name, const std::vector<double>& value);

	virtual default_ReturnedValueFromStript call();
	virtual void give_feedback(const default_FeedbackType& newParams);
};

