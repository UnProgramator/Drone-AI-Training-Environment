#pragma once

#include <map>
#include <irrlicht.h>

typedef void(*map_fun_type)(void);

class MyEventReceiver : public irr::IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent& event) override;
};

extern MyEventReceiver* getEventReceiver();
extern void setMap(const std::map<irr::EKEY_CODE, map_fun_type> &map);
extern void tick_io();
extern map_fun_type addNewKeyFunction(irr::EKEY_CODE key, map_fun_type fun);