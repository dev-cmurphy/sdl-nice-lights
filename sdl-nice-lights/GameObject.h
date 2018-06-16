#pragma once
#include "Vector2.h"
#include <SDL.h>
#include <string>

/*struct GameObject {
Vector2 position;
};*/

struct message {
	Uint8 type;
	Uint16 data;
};

class GameObject
{
public:
	GameObject(std::string tag = "no_tag");
	~GameObject();

	Vector2 position;

	std::string tag; // for debugging purposes

protected:


};

