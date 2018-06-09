#include "stdafx.h"
#include "Actor.h"


Actor::Actor(cWorld* pWorld) {
	_mesh = new cMesh(pWorld);
}


Actor::~Actor() {
	if (_mesh) {
		delete _mesh;
	}
}

bool Actor::load(std::string pPath) {
	if (!_mesh->loadFromFile(pPath)) {
		return false;
	}
	this->setPosition(cVector3d(0,0,0));
}

void Actor::addPointerCollision(HapticPointer* pPointer) {
	if (!_mesh) {
		return;
	}
	_mesh->computeBoundaryBox(true);

	double lSize = cSub(_mesh->getBoundaryMax(), _mesh->getBoundaryMin()).length();

	if (lSize > 0) {
		_mesh->scale(2.0 * pPointer->getWorkspaceRadius() / lSize);
	}
	_mesh->createAABBCollisionDetector(1.01 * pPointer->getProxyRadius(), true, false);
	_mesh->setStiffness(pPointer->getMaxStiffness(), true);
}
void Actor::setFriction(double pStaticFriction, double pDynamicFriction) {
	_mesh->setFriction(pStaticFriction, pDynamicFriction, true);
}
void Actor::setScale(cVector3d pScale) {
	_mesh->scale(pScale);
}
void Actor::setPosition(cVector3d pPosition) {
	_mesh->setPos(pPosition);
}
cVector3d Actor::getPosition() {
	return _mesh->getPos();
}
cMesh* Actor::getMesh() {
	return _mesh;
}