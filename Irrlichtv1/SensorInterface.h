#pragma once

#include <irrlicht.h>

class SensorInterface {
public:
	static bool showRange; //by default is false 

	virtual void setParent(irr::scene::ISceneNode* parent) = 0;
	virtual void setPosition(const irr::core::vector3df& positon) = 0;
	virtual void setOrientation(const irr::core::vector3df& orientation) = 0;

	virtual void getDetectedValue(void* location, size_t locationSize) =0;

	virtual ~SensorInterface() = 0; // abstract class
};

class DistanceSensor : public SensorInterface {
	virtual void setParent(irr::scene::ISceneNode* parent) override;
	virtual void setPosition(const irr::core::vector3df& positon) override;
	virtual void setOrientation(const irr::core::vector3df& orientation) override;

	virtual void getDetectedValue(void* location, size_t locationSize) override;
};