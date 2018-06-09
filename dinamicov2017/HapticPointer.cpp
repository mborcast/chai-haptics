#include "stdafx.h"
#include "HapticPointer.h"


HapticPointer::HapticPointer(cWorld* pWorld, cGenericHapticDevice* pDevice) {
	_tool = new cGeneric3dofPointer(pWorld);
	_tool->setHapticDevice(pDevice);
	_tool->start();
	_tool->m_deviceSphere->setShowEnabled(false);
	_tool->m_proxyPointForceModel->m_collisionSettings.m_checkBothSidesOfTriangles = false;
	_tool->m_proxyPointForceModel->m_useDynamicProxy = true;
}

HapticPointer::~HapticPointer() {
	if (_tool) {
		delete _tool;
	}
}

double HapticPointer::getWorkspaceScaleFactor() {
	if (!_tool) {
		return -1;
	}
	return _tool->getWorkspaceScaleFactor();
}
double HapticPointer::getWorkspaceRadius() {
	if (!_tool) {
		return -1;
	}
	return _workspaceRadius;
}
double HapticPointer::getMaxStiffness() {
	if (!_tool) {
		return -1;
	}
	return _maxStiffness;
}
double HapticPointer::getProxyRadius() {
	if (!_tool) {
		return -1;
	}
	return _proxyRadius;
}
void HapticPointer::setWorkspaceRadius(double pValue) {
	if (!_tool) {
		return;
	}
	_workspaceRadius = pValue;
	_tool->setWorkspaceRadius(_workspaceRadius);
}
void HapticPointer::setProxyRadius(double pValue) {
	if (!_tool) {
		return;
	}
	_proxyRadius = pValue;
	_tool->setRadius(_proxyRadius);
	_tool->m_proxyPointForceModel->setProxyRadius(_proxyRadius);
}
void HapticPointer::setMaxStiffness(double pValue) {
	if (!_tool) {
		return;
	}
	_maxStiffness = pValue / _tool->getWorkspaceScaleFactor();
}

void HapticPointer::update() {
	if (!_tool) {
		return;
	}
	_tool->updatePose();
	_tool->computeInteractionForces();
	_tool->applyForces();
}

void HapticPointer::stop() {
	if (!_tool) {
		return;
	}
	_tool->stop();
}

cGeneric3dofPointer* HapticPointer::getTool() {
	return _tool;
}
