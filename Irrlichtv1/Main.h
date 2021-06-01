#pragma once
#include "JSONParser.h"
#include "Drone.h"
#include "StaticObject.h"
#include "CommunicationInterface.h"

class Main
{
protected:
	Drone* drone;
	std::list<StaticObject*> scene;

public:
	bool init(); // initialise the module, object and process. should be called before main_loop
	bool init_defaults(); // initialise DefaultObjectStorage if not initialised then calls init()

	int main_loop(bool is_training=true); // the main loop

	~Main() = default;
};

