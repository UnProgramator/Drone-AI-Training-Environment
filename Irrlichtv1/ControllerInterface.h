#pragma once

class ControllerInterface {
public:
	virtual ~ControllerInterface() {}
	virtual void tick(float deltaTime) =0;
};