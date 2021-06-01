#include "Main.h"
#include "DefaultObjectStorage.h"
#include "GraphicsManager.h"


bool Main::init()
{
    initGraphicsLibrary(irr::video::E_DRIVER_TYPE::EDT_OPENGL); //initialise the graphics library; this should be the first thing to do in the init function

    if (defObjStorage == nullptr) // check if the defObjStorage is not null; if it is throw exception
        throw new std::exception("defObjStorage was not initialized");
    defObjStorage->check_init_params();

    Base_JSONParser* json_p = defObjStorage->get_JSONParser();

    drone = json_p->parseDrone("./models/Drone.json");
    scene = json_p->parseStaticObjects("./models/DefaultScene.json");

    return true;
}

bool Main::init_defaults()
{
    if (defObjStorage == nullptr)
        defObjStorage = new DefaultObjectStorage();
    return Main::init();
}

int Main::main_loop(bool is_training)
{


    while (renderIsRuning()) {
        renderScene();
    }
    return 0;
}
