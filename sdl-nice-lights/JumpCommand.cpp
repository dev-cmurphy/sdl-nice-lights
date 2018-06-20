#include "JumpCommand.h"



JumpCommand::JumpCommand(GameObject& a) : Command(), actor(a)
{
}


JumpCommand::~JumpCommand()
{
}

void JumpCommand::execute()
{
	std::bitset<64> bitset;
	actor.sendMessage(MSG_JUMP, bitset);
}

void JumpCommand::undo()
{
}
