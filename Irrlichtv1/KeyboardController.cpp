#include "KeyboardController.h"
#include <irrlicht.h>
#include "GraphicsManager.h"
#include <iostream>

using namespace irr;

KeyboardController::KeyboardController():outStrim{&std::cout}
{
}

void KeyboardController::init_parser(int elementCount)
{
	*outStrim << "New initialization with " << elementCount << ":\n";
}

void KeyboardController::parse_double(const char* name, const double value)
{
	*outStrim << "  -variable " << name <<  "parse new double:  " << value << ":\n";
}

void KeyboardController::parse_double_array(const char* name, const std::vector<double>& value)
{
	*outStrim << "  -variable " << name << "parse new double aray:  (";
	for (auto x : value) {
		*outStrim << x << ",";
	}
	*outStrim << "\b)\n";
}

default_ReturnedValueFromStript KeyboardController::call()
{
	default_ReturnedValueFromStript inputs = { 0,0,0 };

	EventReceiver* keycon = EventReceiver::getInstance();

	if (keycon->keyDown(KEY_KEY_W)) {
		inputs.forward = 1;
	}
	else if (keycon->keyDown(KEY_KEY_S)) {
		inputs.forward = -1;
	}

	if (keycon->keyDown(KEY_KEY_D)) {
		inputs.rotation_angle = 1;
	}
	else if (keycon->keyDown(KEY_KEY_A)) {
		inputs.rotation_angle = -1;
	}

	if (keycon->keyDown(KEY_KEY_E)) {
		inputs.up = 1;
	}
	else if (keycon->keyDown(KEY_KEY_Q)) {
		inputs.up = -1;
	}

	return inputs;
}

void KeyboardController::give_feedback(const default_FeedbackType& newParams)
{
	*outStrim << "destinatie " << newParams.destination << ", coordonate curente" << newParams.new_pos << (newParams.hasCollide ? ",s-a produs coliziune" : ",nu e coliziune") << std::endl;
}


