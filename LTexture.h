#pragma once
#include <string>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

class LTexture
{
public:
	static constexpr float kOriginalSize = -1.f;
	LTexture();
	~LTexture();

	bool loadFromFile(SDL_Renderer* renderer, std::string path, bool useColorKey = false);
#if defined(SDL_TTF_MAJOR_VERSION)
	bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor);
#endif
	void destroy();
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setAlpha(Uint8 alhpa);
	void setBlending(SDL_BlendMode blendMode);
	void render(SDL_Renderer* renderer,
		float x,
		float y,
		SDL_FRect* clip = nullptr,
		float width = kOriginalSize,
		float height = kOriginalSize,
		double degrees = 0.0,
		SDL_FPoint* center = nullptr,
		SDL_FlipMode flipMode = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};