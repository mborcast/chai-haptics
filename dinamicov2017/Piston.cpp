#include "stdafx.h"
#include "Piston.h"

Piston::Piston(cWorld* pWorld, double pSpeed) : Actor(pWorld) {
	_angles = 0;
	this->setSpeed(pSpeed);
}

Piston::~Piston() {
}

void Piston::setSpeed(double pValue) {
	_speed = pValue;
}

void Piston::update(double pDt) {
	_angles += pDt * _speed;
	float lOffset = 1 * sin(_angles * CHAI_PI / 180);
	cVector3d lCurrent = this->getPosition();
	this->setPosition(cVector3d(lOffset, lCurrent.y, lCurrent.z));
}