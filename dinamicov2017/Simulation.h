#pragma once
#include "chai3d.h"
#include "SceneGraph.h"

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
	SceneGraph* _sceneGraph;
	double _angles;
	cHapticDeviceHandler* _handler;
	cGeneric3dofPointer* _tool;
	cMesh* _object;
};

