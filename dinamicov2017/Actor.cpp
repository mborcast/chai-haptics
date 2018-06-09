#include "stdafx.h"
#include "Actor.h"


Actor::Actor(cWorld* pWorld) {
	//_object = new cMesh(pWorld);
	//_object->setPos(0.0, 0.0, 0.0);
	//_object->computeBoundaryBox(true);

	//double size = cSub(_object->getBoundaryMax(), _object->getBoundaryMin()).length();

	//if (size > 0) {
	//	_object->scale(2.0 * _tool->getWorkspaceRadius() / size);
	//}

	//_object->createAABBCollisionDetector(1.01 * proxyRadius, true, false);
	//_object->setStiffness(stiffnessMax, true);
	//_object->setFriction(0.1, 0.2, true);
}


Actor::~Actor() {
}

void Actor::instantiate(std::string pPath) {
	//bool fileload = _object->loadFromFile(pPath);
	//if (!fileload) {
	//	//fucked up
	//}
}
