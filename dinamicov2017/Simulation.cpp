#include "stdafx.h"
#include "Simulation.h"


Simulation::Simulation() {
	isRunning = true;
	isFinished = false;

	this->createSceneGraph();
	this->initializeHaptics();
	this->createPistons();
}


Simulation::~Simulation() {
	if (_sceneGraph) {
		delete _sceneGraph;
	}
	if (_hapticDevice) {
		delete _hapticDevice;
	}
	if (_hapticPointer) {
		delete _hapticPointer;
	}
}

void Simulation::createSceneGraph() {
	_sceneGraph = new SceneGraph();
	_sceneGraph->addCamera(
		cVector3d(3.0, 0.0, 0.0),
		cVector3d(0.0, 0.0, 0.0),
		cVector3d(0.0, 0.0, 1.0));
	_sceneGraph->addLight(
		cVector3d(2.0, 0.5, 1.0),
		cVector3d(-2.0, 0.5, 1.0));
}
void Simulation::initializeHaptics() {
	if (!_sceneGraph) {
		return;
	}
	_hapticDevice = new HapticDevice();

	_hapticPointer = new HapticPointer(
		_sceneGraph->getWorld(),
		_hapticDevice->getCurrentDevice());

	_hapticPointer->setWorkspaceRadius(1);
	_hapticPointer->setProxyRadius(0.01);
	_hapticPointer->setMaxStiffness(_hapticDevice->getCurrentDeviceInfo().m_maxForceStiffness);
	_sceneGraph->addChild(_hapticPointer->getTool());
}
void Simulation::createPistons(int pTotal) {
	if (!_sceneGraph) {
		return;
	}
	_piston = new Piston(_sceneGraph->getWorld(), 500);
	_piston->load("../imagenes/cube.obj");
	_piston->addPointerCollision(_hapticPointer);
	_piston->setFriction(0.1, 0.2);
	_piston->setPosition(cVector3d(0, 0, 0));
	_sceneGraph->addChild(_piston->getMesh());
}
void Simulation::updateHaptics() {
	_sceneGraph->updateChildrenPositions(true);
	_hapticPointer->update();
}

void Simulation::update(double pDt) {
	if (_piston) {
		_piston->update(pDt);
	}
}

void Simulation::renderCamera(double pW, double pH) {
	_sceneGraph->renderCameraView(pW, pH);
}
void Simulation::closeGracefully() {
	_hapticPointer->stop();
}