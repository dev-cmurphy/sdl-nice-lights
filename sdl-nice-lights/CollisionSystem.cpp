#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem(int w, int h, int size) : staticComponents(w, h, size), activeComponents(w, h, size)
{
	
}

CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(std::vector<GameObject>& objects)
{
	// deplacement des comps dans les bonnes cells
	for (int i = 0; i < activeComponents.getWidth(); i++) {
		for (int j = 0; j < activeComponents.getHeight(); j++) {

			std::list<CollisionComponent>& comps = activeComponents.getObjectsAt(i, j);

			for (auto a = comps.begin(); a != comps.end();) {

				Vector2& a_pos = objects[a->holder].position;
				Vector2& a_size = a->size;
				Vector2 gridPos = activeComponents.realToGrid(a_pos);

				if ((int)gridPos.x != i || (int)gridPos.y != j) {
					activeComponents.addObjectAt(a_pos, *a);
					a = comps.erase(a);
				}
				else {
					a++;
				}

				std::cout << gridPos.x << ", " << gridPos.y << "\n";
			}
		}
	}

	// collision detection & resolution

	for (int i = 0; i < activeComponents.getWidth(); i++) {
		for (int j = 0; j < activeComponents.getHeight(); j++) {

			std::list<CollisionComponent>& comps = activeComponents.getObjectsAt(i, j);
			std::list<CollisionComponent>& staticComps = staticComponents.getObjectsAt(i, j);

			for (auto a = comps.begin(); a != comps.end(); a++) {
			
				Vector2& a_pos = objects[a->holder].position;
				Vector2& a_size = a->size;

				// collisions avec comps actifs de la cell
				for (auto b = comps.begin(); b != comps.end(); b++) {
					if (a != b) {
						std::cout << "Testing collision\n";
					}
				}

				for (auto s = staticComps.begin(); s != staticComps.end(); s++) {
					std::cout << "Testing coll between active and static";
				}
			}
		}
	}
}

void CollisionSystem::addStaticComponent(int h, Vector2 pos, Vector2 size)
{
	staticComponents.addObjectAt(pos, CollisionComponent(h, pos));
}

void CollisionSystem::addActiveComponent(int h, Vector2 pos, Vector2 size)
{
	activeComponents.addObjectAt(pos, CollisionComponent(h, pos));
}

CollisionSystem::CollisionComponent::CollisionComponent(int h, Vector2 s) : Component(h), size(s)
{
}

CollisionSystem::CollisionComponent::~CollisionComponent()
{
}
