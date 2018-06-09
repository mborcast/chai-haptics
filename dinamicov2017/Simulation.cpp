#include "stdafx.h"
#include "Simulation.h"


Simulation::Simulation() {
	isRunning = true;
	isFinished = false;
	_totalPistons = 0;

	this->createSceneGraph();
	this->initializeHaptics();
	addPiston(500, cVector3d(0, -1, 0));
	addPiston(1800, cVector3d(0, 0, 0));
	addPiston(50, cVector3d(0, 1, 0));
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
		cVector3d(4.0, 0.0, 1.0),
		cVector3d(0.5, 0.0, 0.0),
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
void Simulation::addPiston(double pSpeed, cVector3d pPosition) {
	std::string lPath = "../3dmodels/cube.obj";

	_pistons.push_back(new Piston(_sceneGraph->getWorld(), pSpeed));
	if (_pistons[_totalPistons]->load(lPath)) {
		_pistons[_totalPistons]->addPointerCollision(_hapticPointer);
		_pistons[_totalPistons]->setFriction(0.1, 0.2);
		_pistons[_totalPistons]->setPosition(pPosition);
		_pistons[_totalPistons]->setScale(cVector3d(0.5, 0.5, 0.5));
		_sceneGraph->addChild(_pistons[_totalPistons]->getMesh());
		_totalPistons++;
	}
	else {
		std::cout << "Path: " << lPath << " not found" << std::endl;
		delete _pistons[_totalPistons];
		_pistons.pop_back();
	}
}

void Simulation::updateHaptics() {
	_sceneGraph->updateChildrenPositions(true);
	_hapticPointer->update();
}

void Simulation::update(double pDt) {
	for (unsigned int i = 0; i < _totalPistons; i++) {
		_pistons[i]->update(pDt);
	}
}

void Simulation::renderCamera(double pW, double pH) {
	_sceneGraph->renderCameraView(pW, pH);
}
void Simulation::closeGracefully() {
	_hapticPointer->stop();
}