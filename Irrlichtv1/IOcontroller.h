#pragma once

#include <map>
#include <irrlicht.h>

typedef void(*map_fun_type)(void);

class MyEventReceiver : public irr::IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const irr::SEvent& event) override;
    

    // This is used to check whether a key is being held down
    inline bool IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }

    MyEventReceiver();

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

extern MyEventReceiver* getEventReceiver();
extern void setMap(const std::map<irr::EKEY_CODE, map_fun_type> &map);
extern void tick_io();
extern map_fun_type addNewKeyFunction(irr::EKEY_CODE key, map_fun_type fun);