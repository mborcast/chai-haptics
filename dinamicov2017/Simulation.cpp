#include "stdafx.h"
#include "Simulation.h"


Simulation::Simulation() {
	isRunning = true;
	isFinished = false;
	_angles = 0;

	_sceneGraph = new SceneGraph();
	_sceneGraph->addCamera(
		cVector3d(3.0, 0.0, 0.0),
		cVector3d(0.0, 0.0, 0.0),
		cVector3d(0.0, 0.0, 1.0));
	_sceneGraph->addLight(
		cVector3d(2.0, 0.5, 1.0),
		cVector3d(-2.0, 0.5, 1.0));

	// create a haptic device _handler
	_handler = new cHapticDeviceHandler();
	cGenericHapticDevice* hapticDevice;
	_handler->getDevice(hapticDevice, 0);
	cHapticDeviceInfo info;
	if (hapticDevice) {
		info = hapticDevice->getSpecifications();
	}

	// create a 3D _tool and add it to the world
	_tool = new cGeneric3dofPointer(_sceneGraph->getWorld());
	_tool->setHapticDevice(hapticDevice);
	_tool->start();
	_tool->setWorkspaceRadius(1.0);
	_tool->setRadius(0.01);
	_tool->m_deviceSphere->setShowEnabled(false);
	double proxyRadius = 0.01;
	_tool->m_proxyPointForceModel->setProxyRadius(proxyRadius);
	_tool->m_proxyPointForceModel->m_collisionSettings.m_checkBothSidesOfTriangles = false;
	_tool->m_proxyPointForceModel->m_useDynamicProxy = true;
	double workspaceScaleFactor = _tool->getWorkspaceScaleFactor();
	double stiffnessMax = info.m_maxForceStiffness / workspaceScaleFactor;
	_sceneGraph->addChild(_tool);

	//instantiate actor
	// create a virtual mesh
	_object = new cMesh(_sceneGraph->getWorld());
	_object->setPos(0.0, 0.0, 0.0);
	bool fileload = _object->loadFromFile("../imagenes/cube.obj");
	if (!fileload) {
		//fucked up
	}
	_object->computeBoundaryBox(true);

	double size = cSub(_object->getBoundaryMax(), _object->getBoundaryMin()).length();

	if (size > 0) {
		_object->scale(2.0 * _tool->getWorkspaceRadius() / size);
	}

	_object->createAABBCollisionDetector(1.01 * proxyRadius, true, false);
	_object->setStiffness(stiffnessMax, true);
	_object->setFriction(0.1, 0.2, true);
	_sceneGraph->addChild(_object);
}


Simulation::~Simulation() {
	if (_sceneGraph) {
		delete _sceneGraph;
	}
}

void Simulation::updateHaptics() {
	_sceneGraph->updateChildrenPositions(true);
	_tool->updatePose();
	_tool->computeInteractionForces();
	_tool->applyForces();
}

void Simulation::update(double pDt) {
	_angles += pDt * 500;
	float lOffset = 1 * sin(_angles * CHAI_PI / 180);
	_object->setPos(cVector3d(lOffset, 0, 0));
}

void Simulation::renderCamera(double pW, double pH) {
	_sceneGraph->renderCameraView(pW, pH);
}
void Simulation::closeGracefully() {
	_tool->stop();
}