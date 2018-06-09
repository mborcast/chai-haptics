#include "stdafx.h"
#include "SceneGraph.h"

SceneGraph::SceneGraph() {
	this->createWorld();
}

SceneGraph::~SceneGraph() {
	if (_camera) {
		delete _camera;
	}
	if (_light) {
		delete _light;
	}
	if (_world) {
		delete _world;
	}
}
cWorld* SceneGraph::getWorld() {
	return _world;
}
void SceneGraph::addLight(cVector3d pPosition, cVector3d pDirection) {
	if (!_camera) {
		return;
	}
	_light = new cLight(_world);
	_light->setEnabled(true);
	_light->setPos(pPosition);
	_light->setDir(pDirection);
	_camera->addChild(_light);
}

void SceneGraph::createWorld() {
	_world = new cWorld();
	_world->setBackgroundColor(0, 0, 0.05);
}
void SceneGraph::addCamera(cVector3d pPosition, cVector3d pEye, cVector3d pUpVector) {
	if (!_world) {
		return;
	}
	_camera = new cCamera(_world);
	_camera->set(pPosition, pEye, pUpVector);
	_camera->setClippingPlanes(0.01, 40.0);
	_world->addChild(_camera);
}
void SceneGraph::addChild(cGenericObject* pChild) {
	if (!_world) {
		return;
	}
	_world->addChild(pChild);
}
void SceneGraph::updateChildrenPositions(bool pValue) {
	if (!_world) {
		return;
	}
	_world->computeGlobalPositions(true);
}
void SceneGraph::renderCameraView(double pW, double pH) {
	if (!_camera) {
		return;
	}
	_camera->renderView(pW, pH);
}