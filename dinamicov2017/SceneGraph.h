#pragma once
#include "chai3d.h"
class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();
	cWorld* getWorld();

	void addCamera(
		cVector3d pPosition, 
		cVector3d pEye,
		cVector3d pUpVector);
	void addLight(
		cVector3d pPosition, 
		cVector3d pDirection);
	void addChild(cGenericObject* pChild);

	void updateChildrenPositions(bool pValue);
	void renderCameraView(double pW, double pH);
private:
	cWorld* _world;
	cCamera* _camera;
	cLight* _light;

	void createWorld();
};

