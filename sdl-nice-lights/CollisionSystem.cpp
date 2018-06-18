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
			
				//if (objects[a->holder].hasMessage(MSG_MOVE)) {

				Vector2 delta(objects[a->holder].getMessage(MSG_MOVE));
				
				//gravity here
				//delta += Vector2(0, 1);

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
					a_rect = { (int)(a_pos.x - a_size.x /2), (int)(a_pos.y - a_size.y / 2), (int)a_size.x, (int)a_pos.y };
					a_dRect = { (int)(nextPos.x - a_size.x / 2), (int)(nextPos.y - a_size.y / 2), (int)a_size.x, (int)a_size.y };
					s_rect = { (int)(s_pos.x - s_size.x / 2), (int)(s_pos.y - s_size.y / 2), (int)s_size.x, (int)s_size.y };

					SDL_Rect result;

					if (SDL_IntersectRect(&a_dRect, &s_rect, &result) != SDL_FALSE) {

						Vector2 pen(result.w, result.h);

						/*bool dx = delta.x >= 0;
						bool dy = delta.y >= 0;

						delta.y += result.h * (dy ? -1 : 1);
						delta.x += result.w * (dx ? -1 : 1);*/



						//std::cout << "collision detected!" << pen.x << ", " << pen.y << "\n";
						if (a_pos.x + a_size.x / 2 <= s_pos.x - s_size.x / 2) { // pos précédente à gauche : delta x pos
							delta.x -= result.w;
						}

						if (a_pos.y - a_size.y / 2 >= s_pos.y + s_size.y / 2) {
							delta.y += result.h;
						}
							
						if (a_pos.x - a_size.x / 2 >= s_pos.x + s_size.x / 2) { // pos prec droite : delta x neg
							delta.x += result.w;
						}

						if (a_pos.y + a_size.y / 2 <= s_pos.y - s_size.y / 2) { // pos prec au dessus - delta y pos
							delta.y -= result.h;
						}
					}
				}

				objects[a->holder].position += delta;

				//}

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
