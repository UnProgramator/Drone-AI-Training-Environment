#include "KeyboardController.h"
#include "Drone.h"

KeyboardController::KeyboardController(Drone* drone):
	drone{ drone }
{
}

void KeyboardController::tick(float deltaTime)
{

}

void KeyboardController::moveForward(float value)
{
	drone->moveForwards(value);
}

void KeyboardController::turnRight(float value)
{
	drone->rotateRight(value);
}
