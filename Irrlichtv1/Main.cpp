#include "Main.h"
#include "DefaultObjectStorage.h"
#include "SensorInterface.h"
#include "GraphicsManager.h"
#include "test.pyCommunication.h"
#include "KeyboardController.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <irrlicht.h>
#include "DebugingStubComunicator.h"

int scenario=0;

std::vector<double> Main::genDestination()
{
    std::vector<double> dest = { -1500, -200, 6000 };
    std::vector<double> dest2 = { 8000, 0, 8200 };
    return (scenario == 0) ? dest : dest2;
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
    vector3 pos = drone->getPosition();
    std::cout << "drone init " << pos.X << " " << pos.Y << " " << pos.Z << "\n";
    scene = json_p->parseStaticObjects("./models/DefaultScene.json");

    SensorInterface::setSensorsRangeVisibility(false);

    finishMarker = new StaticObject("models/meshes/finish.obj", "models/meshes/textures/finish.png", {}, {}, { 100,100,100 }, true, false, "finish");

    //comunicator = new pyCommunication(L"", "comunicator",drone->getSensorsNumberOfOutputValues() + 4, drone->getNumberOfInputs(), 0.2f);
    //comunicator = new pyCommunication(L"", "com_test", drone->getSensorsNumberOfOutputValues() + 4, drone->getNumberOfInputs(), 0.2f);
    comunicator = new KeyboardController();
    //comunicator = new DebugingStubComunicator(drone);
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
    finishMarker->setPosition(irr::core::vector3df(destination[0], destination[1], destination[2]));
    float deltaTime = 0;
    std::chrono::duration<double, std::milli> dur;
    std::chrono::system_clock::time_point start, end;
    
    const int val = drone->getSensorsNumber();
    colector->init_parser(val + 2);
    drone->getSensorReadValues(*colector);
    colector->parse_double_array("destinantion", destination);
    colector->parse_double("duration", 0);

    start = end = std::chrono::system_clock::now();

    while (renderIsRuning()) {
        dur = end - start;
        deltaTime = dur.count() / 1000; // dur is in milliseconds, i need
        renderScene();
        if (!pause()) {
            comands = comunicator->call();
            drone->giveCommands(comands);
            //then we tick all data, for now only drone
            drone->tick(deltaTime);

            colector->init_parser(val + 2); // init new parse
            drone->getSensorReadValues(*colector); // read sensors
            colector->parse_double_array("destinantion", destination); // read destination
            colector->parse_double("duration", deltaTime);

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
                //drone->setPosition(genDroneNewPosition()); //to be impelemnted, i forgot ffs
                destination = genDestination();

                colector->init_parser(val + 2); // init new parse
                drone->getSensorReadValues(*colector); // read sensors
                colector->parse_double_array("destinantion", destination); // read destination
                colector->parse_double("duration", 0); // no time has pass since moved
            }


            //verify end
            if (drone->verifyCollision(finishMarker)) {
                scenario = 1;
                destination = genDestination();
                finishMarker->setPosition(irr::core::vector3df( destination[0], destination[1], destination[2]));
            }
        }
        start = end;
        end = std::chrono::system_clock::now();
    }

    clearScene();
    return 0;
}

Main::~Main()
{
    delete drone;
    delete finishMarker;
    delete colector;
    for (auto* x : scene)
        delete x;
}
