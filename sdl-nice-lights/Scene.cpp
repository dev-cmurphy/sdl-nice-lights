#include "Scene.h"

Scene::Scene(SDL_Window* win, Vector2 size) : physics(10, 10, 128), visuals(win, size, &physics), objects(), commands() {
	
	visuals.addLight(Vector2(0, 0), 0, 255, 255, 255, 2);
	visuals.addLight(Vector2(189, 260), 255, 0, 0, 255, 2);

	visuals.setGlobalIllumination(4, 30, 10);
	
	objects.push_back(GameObject());
	objects.back().position = Vector2(200, 200);
	physics.addActiveComponent(0, objects.back().position, Vector2(20, 20));

	objects.push_back(GameObject());
	visuals.addComponent(1, "background.png");
	objects.back().position = Vector2(300, 200);

	objects.push_back(GameObject());
	visuals.addComponent(2, "allo.png");
	objects.back().position = Vector2(100, 300);
	physics.addStaticComponent(2, objects.back().position, Vector2(170,40));


	visuals.addComponent(0, "grr.png");
	
	commands["up"] = SDL_SCANCODE_UP;
	commands["down"] = SDL_SCANCODE_DOWN;
	commands["left"] = SDL_SCANCODE_LEFT;
	commands["right"] = SDL_SCANCODE_RIGHT;
}

Scene::~Scene()
{
}

bool Scene::input()
{
	objects[player].clearMessages();

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	const Uint8 * state = SDL_GetKeyboardState(NULL);

	Vector2 dir;
	if (state[commands["up"]]) {
		dir += Vector2(0, -1);
	}

	if (state[commands["down"]]) {
		dir += Vector2(0, 1);
	}

	if (state[commands["left"]]) {
		dir += Vector2(-1, 0);
	}

	if (state[commands["right"]]) {
		dir += Vector2(1, 0);
	}

	if (dir.sqrMagnitude() > 0) {

		dir.normalize();
		Command* com = new MoveCommand(&objects[player], dir * 100.0f / 17.0f);
		com->execute();
		delete com;

	}

	return true;
}

void Scene::update()
{
	// test msg, to do in something like input comp or movecompwhatever

	/*if (objects[player].hasMessage(MSG_MOVE)) {

		objects[player].position += Vector2(objects[player].getMessage(MSG_MOVE));
	}*/

	visuals.getLight(0).position = objects[player].position;

	physics.update(objects);
}


void Scene::render()
{
	visuals.update(objects);
}
