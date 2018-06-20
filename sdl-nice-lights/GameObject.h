#pragma once
#include "Vector2.h"
#include <SDL.h>
#include <string>
#include <bitset>
#include <unordered_map>

/*struct GameObject {
Vector2 position;
};*/

enum MSG_TYPE
{
	MSG_MOVE = 1,
	MSG_JUMP,
	MSG_FLYING,
	MSG_COLLISION
};

class GameObject
{
public:
	GameObject(std::string tag = "no_tag");
	~GameObject();

	Vector2 position;

	std::string tag; // for debugging purposes

	void sendMessage(MSG_TYPE type, std::bitset<64> data = std::bitset<64>());
	std::bitset<64> getMessage(MSG_TYPE type);
	bool hasMessage(MSG_TYPE t);

	void clearMessages();

protected:
	std::unordered_map<MSG_TYPE, std::bitset<64>> messages;

};

