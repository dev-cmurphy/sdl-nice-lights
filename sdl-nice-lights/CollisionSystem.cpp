#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem(int w, int h, int size) : staticComponents(w, h), activeComponents(w, h), cellSize(size)
{
	
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(std::vector<GameObject>& objects)
{
	//std::cout << "Updating collision system...\n";
	/*for (int i = 0; i < staticComponents.getWidth(); i++) {
		for (int j = 0; j < staticComponents.getHeight(); j++) {
			
			std::list<CollisionComponent>& list = staticComponents.getObjectsAt(i, j);
			for (auto c = list.begin(); c != list.end(); c++) {

				//std::cout << "Component! " << i  << " " << j << " \n";
			}
		}
	}*/
	for (int i = 0; i < staticComponents.getWidth(); i++) {
		for (int j = 0; j < staticComponents.getHeight(); j++) {

			ObjectPooler<CollisionComponent>& comps = staticComponents.getObjectsAt(i, j);
			for (int a = 0; a < comps.activeTotal(); a++) {
			
				Vector2& a_pos = objects[comps[a].holder].position;
				Vector2& a_size = comps[a].size;

				for (int b = a+1; b < comps.activeTotal(); b++) {
					if (a != b) {

					}
				}

			}
		}
	}
}

void CollisionSystem::addStaticComponent(int h, Vector2 pos, Vector2 size)
{
	Vector2 gridPos = pos * (1.0f / (float)cellSize);
	gridPos.x = (int)(gridPos.x + 0.5f);
	gridPos.y = (int)(gridPos.y + 0.5f);
	staticComponents.addObjectAt(gridPos, CollisionComponent(h, pos));
}

CollisionSystem::CollisionComponent::CollisionComponent(int h, Vector2 s) : Component(h), size(s)
{
}

CollisionSystem::CollisionComponent::~CollisionComponent()
{
}
