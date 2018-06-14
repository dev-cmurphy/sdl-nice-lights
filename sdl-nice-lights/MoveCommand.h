#pragma once
#include "Command.h"
#include "GameObject.h"

class MoveCommand : public Command
{
public:
	MoveCommand(GameObject* actor, Vector2 delta);
	~MoveCommand();

	virtual void execute();
	virtual void undo();

protected:
	GameObject * actor;
	Vector2 delta;
};

