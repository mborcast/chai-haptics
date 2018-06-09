#include "stdafx.h"
#include "HapticDevice.h"

HapticDevice::HapticDevice() {
	_handler = new cHapticDeviceHandler();
	_handler->getDevice(_currentDevice, 0);
}

HapticDevice::~HapticDevice() {
	if (_handler) {
		delete _handler;
	}
	if (_currentDevice) {
		delete _currentDevice;
	}
}

cGenericHapticDevice* HapticDevice::getCurrentDevice() {
	return _currentDevice;
}

cHapticDeviceInfo HapticDevice::getCurrentDeviceInfo() {
	if (_currentDevice) {
		return _currentDevice->getSpecifications();
	}
	return cHapticDeviceInfo();
}