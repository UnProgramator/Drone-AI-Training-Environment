#pragma once
class ObjectControllerInterface
{
	
	ObjectControllerInterface(const ObjectControllerInterface&) = delete;
	ObjectControllerInterface(ObjectControllerInterface&&) = delete;
	ObjectControllerInterface& operator=(const ObjectControllerInterface&) = delete;
	ObjectControllerInterface& operator=(ObjectControllerInterface&&) = delete;

public:
	ObjectControllerInterface() =default;
	virtual ~ObjectControllerInterface() = default;
	virtual void tick(float deltaTime) = 0;
};

