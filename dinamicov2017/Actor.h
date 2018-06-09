#pragma once
#include "chai3d.h"
class Actor
{
public:
	Actor(cWorld* pWorld);
	~Actor();
	void instantiate(std::string pPath);
private:
	cMesh* _object;
};

