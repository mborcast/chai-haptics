#pragma once
#include "chai3d.h"
#include "SceneGraph.h"
#include "HapticDevice.h"
#include "HapticPointer.h"
#include "Piston.h"

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
	HapticDevice* _hapticDevice;
	HapticPointer* _hapticPointer;

	int _totalPistons;
	std::vector<Piston*> _pistons;

	void createSceneGraph();
	void initializeHaptics();
	void addPiston(double pSpeed, cVector3d pPosition);
};

