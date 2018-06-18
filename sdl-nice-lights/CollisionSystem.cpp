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

				//std::cout << gridPos.x << ", " << gridPos.y << "\n";
			}
		}
	}

	// collision detection & resolution

	for (int i = 0; i < activeComponents.getWidth(); i++) {
		for (int j = 0; j < activeComponents.getHeight(); j++) {

			std::list<CollisionComponent>& comps = activeComponents.getObjectsAt(i, j);
			std::list<CollisionComponent>& staticComps = staticComponents.getObjectsAt(i, j);

			for (auto a = comps.begin(); a != comps.end(); a++) {
			
				if (objects[a->holder].hasMessage(MSG_MOVE)) {

					Vector2 delta(objects[a->holder].getMessage(MSG_MOVE));

					//std::cout << delta.x << ", " << delta.y << "\n";

					Vector2& a_pos = objects[a->holder].position;
					const Vector2& a_size = a->size;

					Vector2 nextPos = a_pos + delta;


					// collisions avec comps actifs de la cell
					for (auto b = comps.begin(); b != comps.end(); b++) {
						if (a != b) {
							std::cout << "Testing collision\n";
						}
					}

					for (auto s = staticComps.begin(); s != staticComps.end(); s++) {

						Vector2& s_pos = objects[s->holder].position;
						const Vector2& s_size = s->size;


						SDL_Rect a_rect, a_dRect, s_rect;
						a_rect = { (int)a_pos.x, (int)a_pos.y, (int)a_size.x, (int)a_size.y };
						a_dRect = { (int)nextPos.x, (int)nextPos.y, (int)a_size.x, (int)a_size.y };
						s_rect = { (int)s_pos.x, (int)s_pos.y, (int)s_size.x, (int)s_size.y };

						SDL_Rect result;

						if (SDL_IntersectRect(&a_dRect, &s_rect, &result) != SDL_FALSE) {

							Vector2 pen(result.w, result.h);

							std::cout << "collision detected!" << pen.x << ", " << pen.y << "\n";
						}
					}

					objects[a->holder].position += delta;
				}
			}
		}
	}
}

void CollisionSystem::addStaticComponent(int h, Vector2 pos, Vector2 size)
{
	staticComponents.addObjectAt(pos, CollisionComponent(h, size));
}

void CollisionSystem::addActiveComponent(int h, Vector2 pos, Vector2 size)
{
	activeComponents.addObjectAt(pos, CollisionComponent(h, size));
}

CollisionSystem::CollisionComponent::CollisionComponent(int h, Vector2 s) : Component(h), size(s)
{
}

CollisionSystem::CollisionComponent::~CollisionComponent()
{
}
