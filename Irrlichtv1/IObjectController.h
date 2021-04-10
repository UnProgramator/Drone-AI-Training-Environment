#pragma once
class IObjectController
{
	
	IObjectController(const IObjectController&) = delete;
	IObjectController(IObjectController&&) = delete;
	IObjectController& operator=(const IObjectController&) = delete;
	IObjectController& operator=(IObjectController&&) = delete;

public:
	IObjectController() =default;
	virtual ~IObjectController() = default;
	virtual void tick(float deltaTime) = 0;
};

