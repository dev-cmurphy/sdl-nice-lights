#include <iostream>
#include "Scene.h"

int main(int argc, char* argv[]) {

	SDL_Window* window;
	
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("nice lights :)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
	IMG_Init(IMG_INIT_PNG);
	Scene scene(window, Vector2(600, 400));	

	// render to lightmap
	// render lightmap over scene
	//light.setBlendMode(lightBlend);

	// quad tree for physical objects (objects that interact with lights)
	// on itère à travers toutes les lumières 
	// pour chaque lumière on check les zones du quad tree correspondantes
	// à sa position et on découpe la lumière si besoin est
	// => rectToRender = rectTotal au départ, et pour chaque
	// obstacle on réduit le rectToRender

	//class scene
	/*
	
	quadtree<static objects (light affecting)>
	vector pour les lumières (pas assez de lumières pour que ça vaille la peine de pooler

	
	*/

	//class quadtree
	/*
	template <T>
	struct Unit {
		T* unit;
		Vector2 square; // position dans le quadtree
		Vector2 position // position monde réel

		OU

		GameObject* unit
		square
		et la position real world est stockée dans GameObject?
	}
	
	*/

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