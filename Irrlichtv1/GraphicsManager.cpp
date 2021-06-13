#include "GraphicsManager.h"
#include <exception>
#include <iostream>
#include "IOcontroller.h"

irr::		IrrlichtDevice*			device = nullptr;
irr::scene::ISceneManager*			scrMgr = nullptr;
irr::video::IVideoDriver*			vidMgr = nullptr;
irr::gui::  IGUIEnvironment*		guiMgr = nullptr;
irr::scene::ISceneCollisionManager* colMan = nullptr;
irr::scene::ICameraSceneNode*		camera = nullptr;

static const char* unitializedMsg  = "Irrlitch graphics library and global parameters unitialized or invalide";
static const char* meshNotGeneratedMsg  = "Mesh unitialized. Something went rong with irrlicht";
static const char* triangleNotDroppedMsg  = "Triangle selector couldn't be dropped";
static const char* triangleNotCreatedMsg  = "Triangle selector couldn't be created";

using namespace irr;

void initGraphicsLibrary(irr::video::E_DRIVER_TYPE driverType) {

	EventReceiver* envr = EventReceiver::getInstance();

	device = irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(1920, 1080), 16, false, false, false, envr);

	vidMgr  = device->getVideoDriver();
	scrMgr  = device->getSceneManager();
	guiMgr  = device->getGUIEnvironment();
	colMan  = scrMgr->getSceneCollisionManager();
}

void setCamera(const irr::core::vector3df& initialPosition, irr::scene::ISceneNode* parent) {
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	camera = scrMgr->addCameraSceneNodeFPS(parent);
	if(!camera)
		throw std::exception(meshNotGeneratedMsg);
	camera->setPosition(initialPosition);
	camera->setFarValue(50000.f);
}

void renderScene()
{
	vidMgr->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

	scrMgr->drawAll();
	guiMgr->drawAll();

	vidMgr->endScene();
}

irr::scene::IMeshSceneNode* getStaticMesh(const std::string& meshPath, const std::string& texturePath, irr::scene::IMeshSceneNode* parentNode/*0*/, irr::s32 id/*0*/, bool addToRaycast/*true*/){
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	irr::scene::IMeshSceneNode* retVal = nullptr;
	irr::scene::IMesh* mesh = nullptr;

	mesh = scrMgr->getMesh(irr::io::path(meshPath.c_str(), (uint32_t)meshPath.size()));
	if (mesh == nullptr)
		throw std::exception(meshNotGeneratedMsg);

	retVal = scrMgr->addMeshSceneNode(mesh, parentNode, id);
	if (retVal == nullptr)
		throw std::exception(meshNotGeneratedMsg);

	retVal->setMaterialTexture(0, vidMgr->getTexture(texturePath.c_str()));
	retVal->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	if (addToRaycast) {
		irr::scene::ITriangleSelector* selector = scrMgr->createTriangleSelector(retVal->getMesh(), retVal);
		if (selector == nullptr)
			throw std::exception(triangleNotCreatedMsg);
		retVal->setTriangleSelector(selector);
		if (!selector->drop()) {
			//throw std::exception(triangleNotDroppedMsg);
#pragma warning()
		}
	}

	return retVal;
}

irr::scene::IMeshSceneNode* getCube(float scale, irr::s32 id, bool addToRaycast) {
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	irr::scene::IMeshSceneNode* retVal = scrMgr->addCubeSceneNode(scale, 0, id);
	if (!retVal)
		throw std::exception(meshNotGeneratedMsg);
	retVal->setMaterialTexture(0, vidMgr->getTexture("media/default.png"));

	if (addToRaycast) {
		irr::scene::ITriangleSelector* selector = scrMgr->createTriangleSelector(retVal->getMesh(), retVal);
		if (selector == nullptr)
			throw std::exception(triangleNotCreatedMsg);
		retVal->setTriangleSelector(selector);
		if (!selector->drop()) {
			//throw std::exception(triangleNotDroppedMsg);
#pragma warning()
		}
	}
	return retVal;
}

irr::scene::IMeshSceneNode* getSphere(float radius, irr::s32 id, bool addToRaycast)
{
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	irr::scene::IMeshSceneNode* retVal = scrMgr->addSphereSceneNode(radius, 12, 0, id);
	if (!retVal)
		throw std::exception(meshNotGeneratedMsg);
	retVal->setMaterialTexture(0, vidMgr->getTexture("media/default.png"));

	if (addToRaycast) {
		irr::scene::ITriangleSelector* selector = scrMgr->createTriangleSelector(retVal->getMesh(), retVal);
		if (selector == nullptr)
			throw std::exception(triangleNotCreatedMsg);
		retVal->setTriangleSelector(selector);
		if (!selector->drop()) {
			//throw std::exception(triangleNotDroppedMsg);
#pragma warning()
		}
	}

	return retVal;
}


void clearScene() {
	if (scrMgr)
		vidMgr->removeAllHardwareBuffers();
#pragma warning()
#pragma message("\t\t\t\tWARNING:   clearScene need to be finished")
}

EventReceiver* EventReceiver::instance=nullptr;

EventReceiver* EventReceiver::getInstance() {
	if (!instance)
		instance = new EventReceiver();
	return instance;
}

EventReceiver::EventReceiver()
{
	for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		keyValue[i] = false;
}

bool EventReceiver::OnEvent(const irr::SEvent & event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		keyValue[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (event.KeyInput.Key == KEY_ESCAPE)
			exit(0);
	}

	return false;
}

bool EventReceiver::keyDown(irr::EKEY_CODE keyCode) const
{
	return keyValue[keyCode];
}
