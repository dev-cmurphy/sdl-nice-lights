#include <iostream>
#include "Scene.h"

int main(int argc, char* argv[]) {

	SDL_Window* window;
	
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("nice lights :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
	IMG_Init(IMG_INIT_PNG);
	Scene scene(window, Vector2(600, 400));	

	// FPS stuff
	float startClock = 0;
	float deltaClock = 0;
	float FPS = 0;
	startClock = SDL_GetTicks();
	int frames = 0;
	bool quit = false;

	float last = SDL_GetTicks();
	float lag = 0;

	const int MS_PER_PHYSICS_UPDATE = 17;

	while (!quit) {

		float current = SDL_GetTicks();
		float elapsed = current - last;
		last = current;
		lag += elapsed;


		while (lag >= MS_PER_PHYSICS_UPDATE) {
			quit = !scene.input();
			scene.update();
			lag -= MS_PER_PHYSICS_UPDATE;
		}

		scene.render(/*lag / MS_PER_PHYSICS_UPDATE*/);

		frames++;
		if (frames % 1000 == 0) {
			deltaClock = (float)SDL_GetTicks() - startClock;
			startClock = SDL_GetTicks();

			if (deltaClock != 0) {
				FPS = frames * 1000.0f / (float)deltaClock;
				std::cout << deltaClock << ", " << FPS << "\n";
			}
			frames = 0;
		}
	}

	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}