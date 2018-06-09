#pragma once
#include "Actor.h"
class Piston: public Actor
{
public:
	Piston(cWorld* pWorld, double pSpeed);
	~Piston();

	void setSpeed(double pValue);
	void update(double pDt);

private:
	double _speed;
	double _angles;
};

