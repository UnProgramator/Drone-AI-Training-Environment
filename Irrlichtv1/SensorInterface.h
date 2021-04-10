#pragma once

#include <irrlicht.h>
#include <string>
#include "StaticObject.h"

class SensorInterface {
protected:
	static bool showRange; //by default is false 

public:
	static inline void setRangeVisibility(bool isVisible = true) { showRange = isVisible; StaticObject::setVisibilityForAll(isVisible); }
	static inline void toggleRangeVisibility() { showRange = !showRange; StaticObject::setVisibilityForAll(showRange); }

	virtual void setParent(irr::scene::ISceneNode* parent) = 0;
	virtual void setPosition(const irr::core::vector3df& positon) = 0;
	virtual void setOrientation(const irr::core::vector3df& orientation) = 0;

	virtual void getDetectedValue(void* location, size_t locationSize) =0;

	virtual ~SensorInterface() =default;
};

class DistanceSensor : public SensorInterface {
private:
	StaticObject *meshObj, *rangeObj;
	irr::core::vector3df limitPoint;
public:
	using vector3df = irr::core::vector3df;
	DistanceSensor(const std::string& sensorMeshPath, const vector3df& position, const vector3df& rotation, const vector3df& scale, float range);

	virtual void setParent(irr::scene::ISceneNode* parent) override;
	virtual void setPosition(const irr::core::vector3df& positon) override;
	virtual void setOrientation(const irr::core::vector3df& orientation) override;

	virtual void getDetectedValue(void* location, size_t locationSize) override;
};