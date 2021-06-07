#pragma once
#include "JSONParser.h"
#include "Drone.h"
#include "StaticObject.h"
#include "CommunicationInterface.h"


// template<class comunicatyion_type> // need to be templat-ized in future update
//this file is still closed to object
using comunicatyion_type = default_CommunicationInterface;

class Main
{
public:
	using vector3 = irr::core::vector3df;
protected:
	Drone* drone;
	std::list<StaticObject*> scene;
	comunicatyion_type* comunicator = nullptr;
	DataCoolectorInterface* colector;
	int value_size_list;

	std::vector<double> genDestination();
	vector3 genDroneNewPosition();

public:
	bool init(); // initialise the module, object and process. should be called before main_loop
	bool init_with_defaults(); // initialise DefaultObjectStorage if not initialised then calls init()

	int main_loop(bool is_training=true); // the main loop

	~Main() = default;
};

