#pragma once
#include "Scene.h"

class Scene;

class Command
{
public:
	Command();
	virtual ~Command() {};
	virtual void execute() = 0;
	virtual void undo() = 0;
};

