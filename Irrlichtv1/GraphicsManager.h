#pragma once

#include <irrlicht.h>
#include <string>

extern irr::IrrlichtDevice*					device;
extern irr::scene::ISceneManager*			scrMgr;
extern irr::video::IVideoDriver*			vidMgr;
extern irr::gui::  IGUIEnvironment*			guiMgr;
extern irr::scene::ISceneCollisionManager*	colMan;
extern irr::scene::ICameraSceneNode*		camera;

extern void initGraphicsLibrary(irr::video::E_DRIVER_TYPE);
extern void setCamera(const irr::core::vector3df& initialPosition = irr::core::vector3df(0.f, 0.f, 0.f), irr::scene::ISceneNode*parent=0);
extern void clearScene();

extern irr::scene::IMeshSceneNode* getStaticMesh(const std::string & meshPath, const std::string& texturePath, irr::scene::IMeshSceneNode* parentNode = nullptr, irr::s32 id = -1, bool hasCollision = true);
extern irr::scene::IMeshSceneNode* getCube(float scale = 10.f, irr::s32 id = -1, bool hasCollision = true);
extern irr::scene::IMeshSceneNode* getSphere(float radius = 5.f, irr::s32 id = -1, bool hasCollision = false);
