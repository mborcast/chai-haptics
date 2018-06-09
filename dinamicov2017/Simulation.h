#pragma once
#include "chai3d.h"

class Simulation
{
public:
	Simulation();
	~Simulation();
	bool isRunning;
	bool isFinished;

	void updateHaptics();
	void update(double pDt);
	void renderCamera(double pW, double pH);
	void closeGracefully();
private:
	double _angles;
	cWorld * _world;
	cCamera* _camera;
	cLight * _light;
	cHapticDeviceHandler* _handler;
	cGeneric3dofPointer* _tool;
	cMesh* _object;
};

