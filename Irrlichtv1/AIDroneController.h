#pragma once
#include "IObjectController.h"
#include <Python.h>


class AIDroneController :
    public IObjectController
{
    virtual void tick(float deltaTime) override;

    virtual PyObject* getReadValues();
};

