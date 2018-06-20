#include "MoveCommand.h"

MoveCommand::MoveCommand(GameObject& a, Vector2 d) : Command(), actor(a), delta(d)
{
}

MoveCommand::~MoveCommand()
{
}

void MoveCommand::execute()
{
	actor.sendMessage(MSG_MOVE, delta.toBitset());
}

void MoveCommand::undo()
{
	actor.sendMessage(MSG_MOVE, (delta * -1).toBitset());
}
