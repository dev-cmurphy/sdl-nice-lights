#pragma once
#include "ObjectPooler.h"
#include "Component.h"
#include "Texture.h"
#include "CollisionSystem.h"
#include <unordered_map>

class VisualSystem
{
public:
	VisualSystem(SDL_Window*, Vector2 size, CollisionSystem* physics);
	~VisualSystem();

	void update(std::vector<GameObject>& objects);
	void setGlobalIllumination(Uint8 r, Uint8 g, Uint8 b);

	void addComponent(int holder, std::string file, bool newTexture = false);

	struct Light {
		Vector2 position;
		Texture texture;
		float scale;
		SDL_Rect renderRect;
	};

	unsigned int addLight(Vector2 pos = Vector2(), Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255, float scale = 1);
	Light& getLight(unsigned int i);

protected:

	class VisualComponent : public Component {
		friend class VisualSystem;
	public:
		VisualComponent(int holder = -1);
		~VisualComponent();

		std::string textureTag;
	};

	ObjectPooler<VisualComponent> components;

	SDL_Renderer* renderer;

	std::unordered_map<std::string, Texture> textures;

	// lighting stuff
	Texture lightMap;
	std::unordered_map<unsigned int, Light> lights;

	CollisionSystem* physics;
};

