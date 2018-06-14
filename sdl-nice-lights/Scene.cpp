#include "Scene.h"



Scene::Scene(SDL_Window* win, Vector2 size) : physics(10, 10, 128), visuals(win, size, &physics), activeObjects(), commands() {
	
	visuals.addLight(Vector2(0, 0), 255, 255, 255, 255, 1);
	//visuals.addLight(Vector2(0, 20), 120, 255, 120, 255, 2);

	visuals.setGlobalIllumination(10, 10, 10);
	

	visuals.addComponent(&staticObjects.addObjectAt(Vector2(0, 0)), "background.png");
	staticObjects.getObjectsAt(0, 0).back().position = Vector2(201, 300);
	visuals.addComponent(&staticObjects.addObjectAt(Vector2(0, 0)), "allo.png");
	staticObjects.getObjectsAt(0, 0).back().position = Vector2(100, 100);
	
	physics.addStaticComponent(&staticObjects.getObjectsAt(0, 0).back(), Vector2(170, 40));
	visuals.addComponent(&player, "grr.png");
}

Scene::~Scene()
{
}

bool Scene::input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		else if (e.type == SDL_KEYDOWN) {
			player.position += Vector2(2, 2);
			visuals.getLight(0).position += Vector2(1, 1);
		}
	}


	return true;
}


void Scene::render()
{
	physics.update();
	visuals.update();
}
