#include "MoveCommand.h"

MoveCommand::MoveCommand(GameObject* a, Vector2 d) : Command(), actor(a), delta(d)
{
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute()
{
	actor->position += delta;
}

void MoveCommand::undo()
{
	actor->position -= delta;
}
