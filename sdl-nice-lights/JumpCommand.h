#pragma once
#include "Command.h"
#include "GameObject.h"

class JumpCommand :
	public Command
{
public:
	JumpCommand(GameObject& actor);
	~JumpCommand();

	virtual void execute();
	virtual void undo();

protected:
	GameObject & actor;
};

