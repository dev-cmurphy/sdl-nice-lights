#include "GameObject.h"



GameObject::GameObject(std::string t) : tag(t)
{
}


GameObject::~GameObject()
{
}

void GameObject::sendMessage(MSG_TYPE type, std::bitset<64> data)
{
	messages[type] = data;
}

void GameObject::clearMessages()
{
	messages.clear();
}

std::bitset<64> GameObject::getMessage(MSG_TYPE type)
{
	if (messages.find(type) != messages.end())
		return messages[type];

	return std::bitset<64>();
}

bool GameObject::hasMessage(MSG_TYPE t)
{
	return messages.find(t) != messages.end();
}
