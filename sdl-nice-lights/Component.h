#pragma once
#include "GameObject.h"

class Component
{
public:

	Component(int holder = -1);
	virtual ~Component() {};


protected:

	int holder; // index dans le tableau d'entités de la Scene

};

