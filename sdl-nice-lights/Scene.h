#pragma once
#include "Grid.h"
#include "VisualSystem.h"
#include "Command.h"

class Command;

class Scene
{
public:
	Scene(SDL_Window* win, Vector2 size);
	~Scene();
	bool input();
	void render();

private:
	GameObject player;
	std::list<GameObject> activeObjects;

	Grid<GameObject> staticObjects;

	/*
	
	class GameObject
		Vector2 position


	class Component
		GameObject
		(ou int type, int message)
		notify(Uint8 message)
		{	iterate observers et call receive sur chaque
		}

		void receive(Uint8 message) : add message a la queue 
		queue messages


	class DamageComponent : public Component {
		
		System update:
			if whatever
				Uint8 damageMessage = sdf
				notify(damageMessage);
	}

	class VisualComponent : public Component {
		
		visual data etc

		subscribe to DamageComponent

		System update:
			fait le tour des messages de la queue en les popant
			si message >> 2 (w/e) (si message est du bon format? / lisible par le système?)
				damage = message << 4 (asdfgh)
				traitement sur damage 
				switch whatever
	}
	
	*/

	VisualSystem visuals;
	CollisionSystem physics;

	//replace by InputSystem avec queue de undo/redo + return new Commands? avec handleInput() ?
	std::unordered_map<Uint32, Command*> commands;
};

