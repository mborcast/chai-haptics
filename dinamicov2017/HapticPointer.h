#pragma once
#include "chai3d.h"
class HapticPointer
{
public:
	HapticPointer(cWorld* pWorld, cGenericHapticDevice* pDevice);
	~HapticPointer();

	double getWorkspaceScaleFactor();
	double getWorkspaceRadius();
	void setWorkspaceRadius(double pValue);
	void setProxyRadius(double pValue);
	double getProxyRadius();
	double getMaxStiffness();
	void setMaxStiffness(double pValue);
	cGeneric3dofPointer* getTool();

	void update();
	void stop();
private:
	double _proxyRadius;
	double _workspaceRadius;
	double _maxStiffness;
	cGeneric3dofPointer* _tool;
};

