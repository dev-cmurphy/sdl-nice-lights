#include "Texture.h"

Texture::Texture() : file(""), texture(NULL), renderer(NULL) {
	size = Vector2();
}

Texture::Texture(SDL_Renderer* ren, Vector2 s)
{
	texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, s.x, s.y);
	size = s;
	renderer = ren;
	file = "";
}

Texture::Texture(std::string file, SDL_Renderer* renderer) : file(file), renderer(renderer)
{
	texture = loadFromFile(file.c_str());
	int w, h;
	w = h = -1;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	size.x = w;
	size.y = h;
}
Texture::Texture(Texture && tex)
{
	texture = tex.texture;
	file = tex.file;
	size = tex.size;
	renderer = tex.renderer;

	tex.renderer = NULL;
	tex.file = "";
	tex.texture = NULL;
	tex.size = Vector2();
}

Texture::~Texture()
{
	if(texture != NULL)
		SDL_DestroyTexture(texture);

}

void Texture::setColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

void Texture::setAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(texture, a);
}

void Texture::setBlendMode(const SDL_BlendMode& b)
{
	SDL_SetTextureBlendMode(texture, b);
}

Uint8 Texture::getAlphaMod() const
{
	Uint8 a;
	SDL_GetTextureAlphaMod(texture, &a);
	return a;
}

void Texture::getColorMod(Uint8 & r, Uint8 & g, Uint8 & b) const
{
	SDL_GetTextureColorMod(texture, &r, &g, &b);
}

SDL_BlendMode Texture::getBlendMode() const
{
	SDL_BlendMode b;
	SDL_GetTextureBlendMode(texture, &b);
	return b;
}

const Vector2 & Texture::getSize() const
{
	return size;
}

SDL_Texture* Texture::getTexture()
{
	return texture;
}

SDL_Rect Texture::getRect(const Vector2& pos, float scale) const
{
	Vector2 scaled = size * scale;
	SDL_Rect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = scaled.x;
	rect.h = scaled.y;
	return rect;
}

Texture & Texture::operator=(Texture&& tex)
{
	if (&tex != this) {
		if (texture != NULL)
			SDL_DestroyTexture(texture);

		texture = tex.texture;
		file = tex.file;
		size = tex.size;
		renderer = tex.renderer;

		tex.renderer = NULL;
		tex.file = "";
		tex.texture = NULL;
		tex.size = Vector2();
	}

	return *this;
}
/*
Texture & Texture::operator+=(const Texture & other)
{
	SDL_SetRenderTarget(renderer, texture);

	SDL_RenderCopy(renderer, other.texture, NULL, NULL);

	SDL_SetRenderTarget(renderer, NULL);

	return *this;
}*/

SDL_Texture* Texture::loadFromFile(const char * file)
{
	SDL_Texture* texture;
	SDL_Surface* temp = IMG_Load(file);
	if (temp == NULL)
		return NULL;
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	return texture;
}
