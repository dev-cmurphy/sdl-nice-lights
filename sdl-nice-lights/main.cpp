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
	bool quit = false;
	while (!quit) {

		quit = !scene.input();
		scene.render();

		deltaClock = (float)SDL_GetTicks() - startClock;
		startClock = SDL_GetTicks();

		if (deltaClock != 0) {
			FPS = 1000.0f / (float)deltaClock;
			std::cout << deltaClock << ", " << FPS << "\n";
		}
	}

	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}