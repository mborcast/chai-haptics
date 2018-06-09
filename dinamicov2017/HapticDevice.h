#pragma once
#include "chai3d.h"
class HapticDevice
{
public:
	HapticDevice();
	~HapticDevice();
	cHapticDeviceInfo getCurrentDeviceInfo();
	cGenericHapticDevice* getCurrentDevice();
private:
	cHapticDeviceHandler* _handler;
	cGenericHapticDevice* _currentDevice;
};

