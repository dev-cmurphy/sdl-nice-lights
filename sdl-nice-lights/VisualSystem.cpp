#include "VisualSystem.h"
#include <iostream>


VisualSystem::VisualSystem(SDL_Window * win, Vector2 size, CollisionSystem* cols) : renderer(SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)),
lightMap(renderer, size), components(25, true), textures(), lights(), physics(cols)
{
	lightMap.setBlendMode(SDL_BLENDMODE_MOD);
}

void VisualSystem::setGlobalIllumination(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetRenderTarget(renderer, lightMap.getTexture());
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderTarget(renderer, NULL);
}

unsigned int VisualSystem::addLight(Vector2 pos, Uint8 r, Uint8 g, Uint8 b, Uint8 a, float scale)
{
	unsigned int i = lights.size();
	lights[i].texture = Texture("light.png", renderer);
	lights[i].texture.setBlendMode(SDL_BLENDMODE_ADD);
	lights[i].position = pos;
	lights[i].scale = scale;
	lights[i].texture.setColorMod(r, g, b);
	lights[i].texture.setAlpha(a);
	lights[i].renderRect = { (int)pos.x, (int)pos.y, (int)lights[i].texture.getSize().x, (int)lights[i].texture.getSize().y };
	return i;
}

VisualSystem::Light & VisualSystem::getLight(unsigned int i)
{
	return lights[i];
}


void VisualSystem::addComponent(GameObject * go, std::string file, bool newTexture)
{
	VisualComponent* comp = &components.getNew();
	comp->holder = go;

	int total = textures.count(file);
	if (total == 0 || newTexture) {
		textures.insert({ file + (total == 0 ? "" : std::to_string(total)), Texture(file, renderer) });
	}

	comp->textureTag = file;
}

VisualSystem::~VisualSystem()
{
	SDL_DestroyRenderer(renderer);
}

void VisualSystem::update()
{
	SDL_RenderClear(renderer);

	//objects rendering
	SDL_SetRenderTarget(renderer, NULL);

	int activeTotal = components.activeTotal();
	for (int i = 0; i < activeTotal; i++) {
		Texture& ref = textures.at(components[i].textureTag);
		Vector2& pos = components[i].holder->position;
		SDL_RenderCopy(renderer, ref.getTexture(), NULL, &ref.getRect(pos + (ref.getSize() * -0.5f)));
	}

	//lights rendering
	SDL_SetRenderTarget(renderer, lightMap.getTexture());
	SDL_RenderClear(renderer);

	for (auto i = lights.begin(); i != lights.end(); i++) {

		Vector2 gridPos = i->second.position * (1.0f / (float)physics->cellSize);
		gridPos.x = (int)(gridPos.x + 0.5f);
		gridPos.y = (int)(gridPos.y + 0.5f);

		SDL_Rect renderRect, destRect;
		renderRect = i->second.texture.getRect(Vector2(0,0), i->second.scale);
		destRect = i->second.texture.getRect(i->second.position + (i->second.texture.getSize() * -0.5f), i->second.scale);
		//std::cout << gridPos.x << ", " << gridPos.y << "\n";

		for (auto c = physics->staticComponents.getObjectsAt(gridPos.x, gridPos.y).begin();
			c != physics->staticComponents.getObjectsAt(gridPos.x, gridPos.y).end(); c++) {

			// si light under obj et dist light obj < lightRadius alors cut top of light
			Vector2 cPos = c->holder->position;
			Vector2 lPos = i->second.position;
			float yDist = cPos.y - lPos.y;
			std::cout << yDist << "\n";
			Vector2 texSize = i->second.texture.getSize();

			if (yDist < 0 && SDL_abs(yDist) < (texSize.y / 2) - (c->size.y / 2)) {
				//partie qu'on veut cacher : lHeight / 2   - abs(yDist) 
				renderRect.h = (texSize.y / 2) - yDist - (c->size.y / 2);
				renderRect.y += (texSize.y / 2) + yDist + (c->size.y / 2);

				destRect.h = renderRect.h;
				destRect.y += (texSize.y / 2) + yDist + (c->size.y / 2);
			}

			if (yDist >= 0 && SDL_abs(yDist) < (texSize.y / 2) - (c->size.y / 2)) {
				//partie qu'on veut cacher : lHeight / 2   - abs(yDist) 
				renderRect.h = (texSize.y / 2) + yDist - (c->size.y / 2);
				//renderRect.y += (texSize.y / 2) + yDist + (c->size.y / 2);

				destRect.h = renderRect.h;
				//destRect.y += (texSize.y / 2) + yDist + (c->size.y / 2);
			}
		}
		SDL_RenderCopy(renderer, i->second.texture.getTexture(), &renderRect, &destRect);
	}

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, lightMap.getTexture(), NULL, NULL);

	SDL_RenderPresent(renderer);
}

VisualSystem::VisualComponent::VisualComponent(GameObject * h) : Component(h)
{
}

VisualSystem::VisualComponent::~VisualComponent()
{
}
