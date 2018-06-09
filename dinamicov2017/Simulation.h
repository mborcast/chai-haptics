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

	Piston* _piston;

	void createSceneGraph();
	void initializeHaptics();
	void createPistons(int pTotal);
};

