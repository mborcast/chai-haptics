#pragma once
#include "chai3d.h"
#include "HapticPointer.h"
class Actor
{
public:
	Actor(cWorld* pWorld);
	~Actor();
	void setPosition(cVector3d pPosition);
	bool load(std::string pPath);
	void setFriction(double pStaticFriction, double pDynamicFriction);
	void addPointerCollision(HapticPointer* pPointer);
	virtual void update(double pDt) = 0;
	cMesh* getMesh();
private:
	cMesh* _mesh;
};

