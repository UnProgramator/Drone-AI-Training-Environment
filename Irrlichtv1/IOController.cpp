#include "IOcontroller.h"
#include <irrlicht.h>
#include <iostream>

static std::map<irr::EKEY_CODE, map_fun_type> map_apel;


// This is the one method that we have to implement
bool MyEventReceiver::OnEvent(const irr::SEvent& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

    return false;
}

MyEventReceiver::MyEventReceiver()
{
    for (uint32_t i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

static class MyEventReceiver evrec;

MyEventReceiver* getEventReceiver() {
    return &evrec;
}

void setMap(const std::map<irr::EKEY_CODE, map_fun_type> &map)
{
    map_apel = map;
}

void tick_io()
{
    for (auto payr : map_apel) {
        if (evrec.IsKeyDown(payr.first))
            payr.second();
    }
}

map_fun_type addNewKeyFunction(irr::EKEY_CODE key, map_fun_type fun) 
{
    map_fun_type retVal = nullptr;
    if (map_apel.count(key) > 0)
        retVal = map_apel[key];
    map_apel[key] = fun;
    return retVal;
}




