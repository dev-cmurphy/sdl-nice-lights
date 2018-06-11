#pragma once
#include "GameObject.h"
#include <queue>
#include <vector>
#include <SDL.h>

class Component
{
public:

	Component(GameObject* holder = NULL);
	virtual ~Component() {};

	void notify(Uint8 message);
	void receive(Uint8 message);

protected:

	GameObject * holder;

	std::vector<Component*> observers;
	std::queue<Uint8> messages;
};

