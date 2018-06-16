#include "Scene.h"

Scene::Scene(SDL_Window* win, Vector2 size) : physics(10, 10, 128), visuals(win, size, &physics), objects(), commands() {
	
	visuals.addLight(Vector2(0, 0), 255, 255, 255, 255, 1);
	//visuals.addLight(Vector2(0, 20), 120, 255, 120, 255, 2);

	visuals.setGlobalIllumination(40, 30, 10);
	
	objects.push_back(GameObject());
	objects.push_back(GameObject());
	visuals.addComponent(1, "background.png");
	objects.back().position = Vector2(300, 200);

	objects.push_back(GameObject());
	visuals.addComponent(2, "allo.png");
	objects.back().position = Vector2(100, 100);
	
	//physics.addStaticComponent(&staticObjects.getObjectsAt(0, 0).back(), Vector2(170, 40));

	for (int i = 0; i < 100; i++) {
		objects.push_back(GameObject());
		physics.addStaticComponent(i + 3, objects[i+3].position, Vector2(171, 40));
	}

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

		visuals.getLight(0).position = objects[player].position;
	}

	return true;
}

void Scene::update()
{
	// test msg, to do in something like input comp or movecompwhatever

	if (objects[player].hasMessage(MSG_MOVE)) {

		objects[player].position += Vector2(objects[player].getMessage(MSG_MOVE));
	}

	physics.update(objects);
}


void Scene::render()
{
	visuals.update(objects);
}
