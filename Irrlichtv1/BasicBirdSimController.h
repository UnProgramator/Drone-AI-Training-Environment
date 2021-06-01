#pragma once
#include "ObjectControllerInterface.h"
#include "DynamicObject.h"
#include <irrlicht.h>

class BasicBirdSimController :
    public ObjectControllerInterface
{
    using vector3 = irr::core::vector3df;

    const uint8_t bDestroyOnDelete:1, bIsResting:1; //booleans
    DynamicObject* body;
    const float maxSpeed, maxAltitude, maxStamina;
    float stamina;
    float crtMovementDistance = 0;
    vector3 crtRotation = vector3(0.f,0.f,0.f);

public:
    //deleted operators and constructors
    BasicBirdSimController(BasicBirdSimController&&) = delete;
    BasicBirdSimController(const BasicBirdSimController&) = delete;
    BasicBirdSimController& operator=(const BasicBirdSimController&) = delete;
    BasicBirdSimController& operator=(BasicBirdSimController&&) = delete;

    BasicBirdSimController(DynamicObject* body, const float maxSpeed, const float maxAltitude, const float maxStamina, bool deleteOnObjectDestruction = true);
    ~BasicBirdSimController();
    virtual void tick(float deltaTime) override;
};

