#pragma once
#include "ObjectControllerInterface.h"
#include "Drone.h"

class KeyboardController :
    public ObjectControllerInterface
{
private:
	Drone* drone;
public:
	KeyboardController(Drone* drone);
	virtual ~KeyboardController() {};
	virtual void tick(float deltaTime);
	virtual void moveForward(float value);
	virtual void turnRight(float value);

	inline void moveFront() { this->moveForward(1.f);  }
	inline void moveBack()  { this->moveForward(-1.f); }
	inline void turnRight() { this->turnRight(1.f);  }
	inline void turnLeft()  { this->turnRight(-1.f); }
};

