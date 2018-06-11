#include "Component.h"



Component::Component(GameObject* h) : holder(h), observers(), messages()
{
}

void Component::notify(Uint8 message)
{
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->receive(message);
	}
}

void Component::receive(Uint8 message)
{
	messages.emplace(message);
}
