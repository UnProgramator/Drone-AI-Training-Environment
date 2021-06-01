#include "BasicBirdSimController.h"

BasicBirdSimController::BasicBirdSimController(DynamicObject* body, const float maxSpeed, const float maxAltitude, const float maxStamina, bool deleteOnObjectDestruction):
	maxAltitude{maxAltitude}, maxSpeed{ maxSpeed }, maxStamina{ maxStamina }, body{body}, stamina{maxStamina}, bDestroyOnDelete{deleteOnObjectDestruction}, bIsResting{false}
{
}

BasicBirdSimController::~BasicBirdSimController()
{
	if(bDestroyOnDelete)
		delete body;
}

void BasicBirdSimController::tick(float deltaTime)
{
}
