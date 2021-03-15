#include "GraphicsManager.h"
#include <exception>
#include <iostream>

irr::		IrrlichtDevice*			device = nullptr;
irr::scene::ISceneManager*			scrMgr = nullptr;
irr::video::IVideoDriver*			vidMgr = nullptr;
irr::gui::  IGUIEnvironment*		guiMgr = nullptr;
irr::scene::ISceneCollisionManager* colMan = nullptr;
irr::scene::ICameraSceneNode*		camera = nullptr;

static const char* unitializedMsg  = "Irrlitch graphics library and global parameters unitialized or invalide";
static const char* meshNotGeneratedMsg  = "Mesh unitialized. Something went rong with irrlicht";
static const char* triangleNotDroppedMsg  = "Triangle selector couldn't be dropped";

void initGraphicsLibrary(irr::video::E_DRIVER_TYPE driverType) {
	device = irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(2150, 1240), 16, false, false, false, nullptr);

	vidMgr  = device->getVideoDriver();
	scrMgr  = device->getSceneManager();
	guiMgr  = device->getGUIEnvironment();
	colMan  = scrMgr->getSceneCollisionManager();
}

void setCamera(const irr::core::vector3df& initialPosition) {
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	camera = scrMgr->addCameraSceneNodeFPS();
	if(!camera)
		throw std::exception(meshNotGeneratedMsg);
	camera->setPosition(initialPosition);
}

irr::scene::IMeshSceneNode* getStaticMesh(const std::string& path, irr::s32 id) {
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	irr::scene::IMeshSceneNode* retVal = nullptr;

	if(!retVal)
		throw std::exception(meshNotGeneratedMsg);
	return retVal;
}

irr::scene::IMeshSceneNode* getCube(float scale, irr::s32 id) {
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	irr::scene::IMeshSceneNode* retVal = scrMgr->addCubeSceneNode(scale, scrMgr->getRootSceneNode(), id);;
	if (!retVal)
		throw std::exception(meshNotGeneratedMsg);
	return retVal;
}

void addToCollision(irr::scene::IMeshSceneNode* object)
{
	irr::scene::ITriangleSelector* selector = scrMgr->createTriangleSelector(object->getMesh(), object);
	object->setTriangleSelector(selector);
	if (!selector->drop()) {
		throw std::exception(triangleNotDroppedMsg);
	}
}

void addToCollision(irr::scene::IAnimatedMeshSceneNode* object)
{
	irr::scene::ITriangleSelector*  selector = scrMgr->createTriangleSelector(object);
	object->setTriangleSelector(selector);
	if (!selector->drop()) {
		throw std::exception(triangleNotDroppedMsg);
	}
}

void clearScene() {
	if (scrMgr)
		vidMgr->removeAllHardwareBuffers();
#pragma warning()
#pragma message("\t\t\t\tWARNING:   clearScene need to be finished")
}


