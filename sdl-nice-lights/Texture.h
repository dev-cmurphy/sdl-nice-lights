#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Vector2.h"
#include <string>

class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* ren, Vector2 size);
	Texture(std::string file, SDL_Renderer * ren);
	Texture(Texture&& tex);
	~Texture();

	void setColorMod(Uint8 r, Uint8 g, Uint8 b);
	void setAlpha(Uint8 a);
	void setBlendMode(const SDL_BlendMode&);

	Uint8 getAlphaMod() const;
	void getColorMod(Uint8& r, Uint8& g, Uint8& b) const;
	SDL_BlendMode getBlendMode() const;

	const Vector2 & getSize() const;
	SDL_Texture* getTexture();
	SDL_Rect getRect(const Vector2& pos = Vector2(), float scale = 1) const;

	Texture& operator=(Texture&& t);
	//Texture& operator+=(const Texture&);

private:

	std::string file;
	Vector2 size;
	SDL_Texture * texture;
	SDL_Renderer * renderer;
	SDL_Texture * loadFromFile(const char* file);

	//static std::unordered_map<int, SDL_Texture*> textureCollection;
};

