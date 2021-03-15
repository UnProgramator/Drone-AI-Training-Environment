#pragma once
class IObjectController
{
	IObjectController() = delete;
	IObjectController(const IObjectController&) = delete;
	IObjectController(IObjectController&&) = delete;
	IObjectController& operator=(const IObjectController&) = delete;
	IObjectController& operator=(IObjectController&&) = delete;

public:
	virtual ~IObjectController() = 0;
	virtual void tick(float deltaTime) = 0;
};

