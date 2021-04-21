#pragma once
#include "ObjectControllerInterface.h"
#include <Python.h>


class AIDroneController :
    public ObjectControllerInterface
{
    virtual void tick(float deltaTime) override;

    virtual PyObject* getReadValues();
};

