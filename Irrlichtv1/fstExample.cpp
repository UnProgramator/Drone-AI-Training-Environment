#include <irrlicht.h>
#include <IMeshSceneNode.h>
#include <iostream>
#include <string>

#include "GraphicsManager.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "IOcontroller.h"
#include "KeyboardController.h"


namespace alex_example {
	namespace fst_example {
		class cube {

			irr::scene::IMeshSceneNode* cubeNode;
			irr::core::vector3df position;


		public:


			cube() : cube(irr::core::vector3df(0, 0, 30)) {}

			cube(const irr::core::vector3df& initialCoordinates, float scale = 10.f) {

				cubeNode = scrMgr->addCubeSceneNode(scale, scrMgr->getRootSceneNode(), -1, initialCoordinates);
				cubeNode->setMaterialTexture(0, vidMgr->getTexture("media/t351sml.jpg"));
				cubeNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				position = initialCoordinates;

				irr::scene::ITriangleSelector* selector = scrMgr->createTriangleSelector(cubeNode->getMesh(), cubeNode);
				cubeNode->setTriangleSelector(selector);
				selector->drop();
			}

			void addMovement(const irr::core::vector3df& positionOffset) {
				position += positionOffset;
				cubeNode->setPosition(position);
			}

			bool colideWith(const cube& other) {
				return this->cubeNode->getTransformedBoundingBox().intersectsWithBox(other.cubeNode->getTransformedBoundingBox());
			}

			const irr::core::vector3df& getPosition() const {
				return position;
			}
		};

		std::ostream& operator<<(std::ostream& out, const irr::core::vector3df& vec) {
			return out << "(" << vec.X << "," << vec.Y << "," << vec.Z << ")";
		}

		class sensor {
			irr::scene::IMeshSceneNode* extremities[2];
			irr::core::vector3df direction;
			irr::core::vector3df pos;


		public:
			sensor(const irr::core::vector3df& initialCoordinates = irr::core::vector3df(0, 0, 30), const irr::core::vector3df& direction = irr::core::vector3df(0, 0, 1), float range = 10.f) : direction(direction) {
				pos = initialCoordinates;
				this->direction.normalize();
				this->direction *= range;

				extremities[0] = scrMgr->addSphereSceneNode();
				extremities[0]->setPosition(initialCoordinates);
				extremities[0]->setScale(irr::core::vector3df(0.25f, 0.25f, 0.25f));

				extremities[1] = scrMgr->addSphereSceneNode();
				extremities[1]->setPosition(pos + direction);
				extremities[1]->setScale(irr::core::vector3df(0.25f, 0.25f, 0.25f));
			}

			void addMovement(const irr::core::vector3df& positionOffset) {
				pos += positionOffset;

				extremities[0]->setPosition(pos);
				extremities[1]->setPosition(pos + direction);

			}

			float detect() {
				irr::core::line3df ray(pos, pos + direction);

				irr::core::vector3df pointOfColision;
				irr::core::triangle3df colisionTriangle;

				if (colMan->getSceneNodeAndCollisionPointFromRay(ray, pointOfColision, colisionTriangle))
					return (pointOfColision - pos).getLength();
				return INFINITY;
			}

			const irr::core::vector3df& getPosition() const {
				return pos;
			}
		};

		int main() {

			bool b = true, b2 = true;

			initGraphicsLibrary(irr::video::EDT_OPENGL);
			setCamera();

			cube c1, c2(irr::core::vector3df(0, 20, 30));
			sensor s1(irr::core::vector3df(0, 0, 30) + irr::core::vector3df(12.f, 0.f, 0.f), irr::core::vector3df(-1.f, 0.f, 0.f), 15.f);



			irr::gui::IGUIStaticText* coli = guiMgr->addStaticText(L"no colision", irr::core::rect<irr::s32>(10, 10, 260, 22), true);
			irr::gui::IGUIStaticText* dist = guiMgr->addStaticText(L"INF", irr::core::rect<irr::s32>(10, 24, 260, 36), true);

			while (device->run())
			{
				vidMgr->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

				scrMgr->drawAll();
				guiMgr->drawAll();

				vidMgr->endScene();

				c2.addMovement(irr::core::vector3df(0.f, -0.01f, 0.f));

				if (b && c2.colideWith(c1)) {
					coli->setText(L"collision started");
					b = false;
				}
				else if (!b && !c2.colideWith(c1)) {
					coli->setText(L"collision finished");
					b = true;
				}

				if (s1.getPosition().X < 30.f && b2)
					s1.addMovement(irr::core::vector3df(0.005f, 0.f, 0.f));
				else
					b2 = false;
				if (s1.getPosition().X > 5.f && !b2)
					s1.addMovement(irr::core::vector3df(-0.005f, 0.f, 0.f));
				else
					b2 = true;

				float value = s1.detect();

				std::wstring v = std::to_wstring(value);
				dist->setText(v.c_str());
			}
			return 0;
		}
	}
	namespace snd_example{
		int main() {

			initGraphicsLibrary(irr::video::EDT_OPENGL);
			setCamera();

			StaticObject *o1, *o2;
			DynamicObject *d1, *d2;

			o1 = new StaticObject(getStaticMesh("media/faerie.md2", "media/Faerie5.bmp"), irr::core::vector3df(0.f, 0.f, 50.f));
			o2 = new StaticObject(getStaticMesh("media/gun.md2", "media/gun.jpg"), irr::core::vector3df(0.f, 0.f, 50.f));
			d1 = new DynamicObject(getCube(), irr::core::vector3df());
			d1 = new DynamicObject(getCube(), irr::core::vector3df(-10.f, 10.f, 5.f));

			addNewKeyFunction(irr::KEY_ESCAPE, []() {exit(0); });

			while (device->run()) {
				vidMgr->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

				scrMgr->drawAll();

				vidMgr->endScene();

				d1->addInputVector(d1->getForwardVector() * 0.2f * (rand()%3-1));
			}

			return 0;
		}
	}
	namespace trd_example {

		KeyboardController* keyCon;

		void moveFront() {
			keyCon->moveFront();
		}

		void moveBack() {
			keyCon->moveBack();
		}

		void turnRight() {
			keyCon->turnRight();
		}

		void turnLeft() {
			keyCon->turnLeft();
		}

		int main() {

			initGraphicsLibrary(irr::video::EDT_OPENGL);

			addNewKeyFunction(irr::KEY_ESCAPE, []() {exit(0); });
			addNewKeyFunction(irr::KEY_KEY_W, moveFront);
			addNewKeyFunction(irr::KEY_KEY_S, moveBack);
			addNewKeyFunction(irr::KEY_KEY_A, turnLeft);
			addNewKeyFunction(irr::KEY_KEY_D, turnRight);

			Drone* drone = new Drone(irr::core::vector3df(-10.f, 10.f, 5.f), irr::core::vector3df(0.f, 0.f, 0.f), irr::core::vector3df(1.f, 0.f, 0.f));
			keyCon = new KeyboardController(drone);
			setCamera(irr::core::vector3df(), drone->getParent());

			while (device->run()) {
				vidMgr->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

				scrMgr->drawAll();

				vidMgr->endScene();

				std::cout << vidMgr->getFPS() << std::endl;

				drone->tick();

				tick_io();
			}

			return 0;
		}
	}
}