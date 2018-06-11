#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem(int w, int h, int size) : staticComponents(w, h), activeComponents(w, h), cellSize(size)
{
	
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update()
{
	//std::cout << "Updating collision system...\n";
	for (int i = 0; i < staticComponents.getWidth(); i++) {
		for (int j = 0; j < staticComponents.getHeight(); j++) {
			
			std::list<CollisionComponent>& list = staticComponents.getObjectsAt(i, j);
			for (auto c = list.begin(); c != list.end(); c++) {

				//std::cout << "Component! " << i  << " " << j << " \n";
			}
		}
	}
}

void CollisionSystem::addStaticComponent(GameObject * h, Vector2 size)
{
	Vector2 pos = h->position;
	Vector2 gridPos = pos * (1.0f / (float)cellSize);

	staticComponents.addObjectAt(gridPos, CollisionComponent(h, size));
}

CollisionSystem::CollisionComponent::CollisionComponent(GameObject * h, Vector2 s) : Component(h), size(s)
{
}

CollisionSystem::CollisionComponent::~CollisionComponent()
{
}
