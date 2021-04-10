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

void initGraphicsLibrary(irr::video::E_DRIVER_TYPE driverType) {
	device = irr::createDevice(driverType, irr::core::dimension2d<irr::u32>(2150, 1240), 16, false, false, false, getEventReceiver());

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
}

irr::scene::IMeshSceneNode* getStaticMesh(const std::string& meshPath, const std::string& texturePath, irr::scene::IMeshSceneNode* parentNode/*0*/, irr::s32 id/*0*/, bool hasCollision/*true*/){
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

	irr::scene::ITriangleSelector* selector = scrMgr->createTriangleSelector(retVal->getMesh(), retVal);
	if (selector == nullptr)
		throw std::exception(triangleNotCreatedMsg);
	retVal->setTriangleSelector(selector);
	if (!selector->drop()) {
		//throw std::exception(triangleNotDroppedMsg);
#pragma warning()
	}

	return retVal;
}

irr::scene::IMeshSceneNode* getCube(float scale, irr::s32 id, bool hasCollision) {
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	irr::scene::IMeshSceneNode* retVal = scrMgr->addCubeSceneNode(scale, 0, id);
	if (!retVal)
		throw std::exception(meshNotGeneratedMsg);
	retVal->setMaterialTexture(0, vidMgr->getTexture("media/default.png"));
	return retVal;
}

irr::scene::IMeshSceneNode* getSphere(float radius, irr::s32 id, bool hasCollision)
{
	if (scrMgr == nullptr) {
		throw std::exception(unitializedMsg);
	}
	irr::scene::IMeshSceneNode* retVal = scrMgr->addSphereSceneNode(radius, 12, 0, id);
	if (!retVal)
		throw std::exception(meshNotGeneratedMsg);
	retVal->setMaterialTexture(0, vidMgr->getTexture("media/default.png"));
	return retVal;
}


void clearScene() {
	if (scrMgr)
		vidMgr->removeAllHardwareBuffers();
#pragma warning()
#pragma message("\t\t\t\tWARNING:   clearScene need to be finished")
}


