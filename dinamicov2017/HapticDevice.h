#pragma once
#include "chai3d.h"
class HapticDevice
{
public:
	HapticDevice();
	~HapticDevice();
private:
	cHapticDeviceHandler* _handler;
};

