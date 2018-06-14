#include <iostream>
#include "Scene.h"

int main(int argc, char* argv[]) {

	SDL_Window* window;
	
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("nice lights :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
	IMG_Init(IMG_INIT_PNG);
	Scene scene(window, Vector2(600, 400));	

	bool quit = false;
	while (!quit) {

		quit = !scene.input();
		scene.render();
		
	}

	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return 0;
}