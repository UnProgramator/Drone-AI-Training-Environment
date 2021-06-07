#include "Main.h"
#include "DefaultObjectStorage.h"
#include "GraphicsManager.h"
#include "test.pyCommunication.h"
#include <vector>

std::vector<double> Main::genDestination()
{
    std::vector<double> dest = { 100, 0, 0 };
    return dest;
}

Main::vector3 Main::genDroneNewPosition()
{
    return vector3();
}

bool Main::init()
{
    initGraphicsLibrary(irr::video::E_DRIVER_TYPE::EDT_DIRECT3D9); //initialise the graphics library; this should be the first thing to do in the init function
    setCamera();

    if (defObjStorage == nullptr) // check if the defObjStorage is not null; if it is throw exception
        throw new std::exception("defObjStorage was not initialized");
    defObjStorage->check_init_params();

    Base_JSONParser* json_p = defObjStorage->get_JSONParser();

    drone = json_p->parseDrone("./models/Drone.json");
    //scene = json_p->parseStaticObjects("./models/DefaultScene.json");

    comunicator = new pyCommunication(L"./../../Irrlichtv1/", "comunicator",drone->getSensorsNumberOfOutputValues() + 3, drone->getNumberOfInputs(), 0.2f);
    colector = dynamic_cast<DataCoolectorInterface*>(comunicator);
    if (colector == nullptr)
        throw std::exception("cast error occured i Main::init");

    return true;
}

bool Main::init_with_defaults()
{
    if (defObjStorage == nullptr)
        defObjStorage = new DefaultObjectStorage();
    return Main::init();
}

int Main::main_loop(bool is_training)
{
    default_ReturnedValueFromStript comands;
    default_FeedbackType feedback = {};
    std::vector<double> destination = genDestination();
    float deltaTime = 0;

    colector->init_parser(drone->getSensorsNumberOfOutputValues() + 3);
    drone->getSensorReadValues(*colector);
    colector->parse_double_array("destinantion", destination);

    while (renderIsRuning()) {
        renderScene();
        comands = comunicator->call();
        drone->giveCommands(comands);

        //then we tick all data, for now only drone
        drone->tick(deltaTime);

        colector->init_parser(drone->getSensorsNumberOfOutputValues() + 3); // init new parse
        drone->getSensorReadValues(*colector); // read sensors
        colector->parse_double_array("destinantion", destination); // read destination

        feedback.hasCollide = false;
        for (auto* sobj : scene) {
            if (drone->verifyCollision(sobj))
                feedback.hasCollide = true;
        }

        if (is_training) {
            feedback.new_pos[0] = drone->getPosition().X;
            feedback.new_pos[1] = drone->getPosition().Y;
            feedback.new_pos[2] = drone->getPosition().Z;
            feedback.destination[0] = destination[0];
            feedback.destination[1] = destination[1];
            feedback.destination[2] = destination[2];
            comunicator->give_feedback(feedback);
        }

        if (feedback.hasCollide) {
            drone->reset();
            //drone->setPosition(genDroneNewPosition());
            destination = genDestination();

            colector->init_parser(drone->getSensorsNumberOfOutputValues() + 3); // init new parse
            drone->getSensorReadValues(*colector); // read sensors
            colector->parse_double_array("destinantion", destination); // read destination
        }
    }

    clearScene();
    return 0;
}
