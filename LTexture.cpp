#include "Ltexture.h"

LTexture::LTexture() :
	mTexture{ nullptr },
	mWidth{ 0 },
	mHeight{ 0 }
{

}

LTexture::~LTexture()
{
	destroy();
}

bool LTexture::loadFromFile(SDL_Renderer* renderer, std::string path, bool useColorKey)
{
	destroy();

	path = "assets/" + path;
	SDL_Surface* loadedsurface = IMG_Load(path.c_str());
	if (loadedsurface == nullptr)
	{
		SDL_Log("Unable to load image via path: %s", path.c_str());
	}
	else
	{
		if (!SDL_SetSurfaceColorKey(loadedsurface, true, SDL_MapSurfaceRGB(loadedsurface, 0x00, 0xFF, 0xFF)))
		{
			SDL_Log("Unable to color key!");
		}
		else
		{
			mTexture = SDL_CreateTextureFromSurface(renderer, loadedsurface);
			if (mTexture == nullptr)
			{
				SDL_Log("Unable to create texture!");
			}
			else
			{
				mWidth = loadedsurface->w;
				mHeight = loadedsurface->h;
			}
		}


		SDL_DestroySurface(loadedsurface);
	}

	return mTexture != nullptr;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor)
{
	destroy();

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, textureText.c_str(), 0, textColor);
	if (textSurface == nullptr)
	{
		SDL_Log("Unable to render text surface!");
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == nullptr)
		{
			SDL_Log("Unable to create texture from rendered text!");
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_DestroySurface(textSurface);
	}

	return mTexture != nullptr;
}
#endif

void LTexture::destroy()
{
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::setBlending(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(mTexture, blendMode);
}

void LTexture::render(SDL_Renderer* renderer, float x, float y, SDL_FRect* clip, float width, float height, double degrees, SDL_FPoint* center,	SDL_FlipMode flipMode)
{
	SDL_FRect dstRect = { x, y, static_cast<float>(mWidth), static_cast<float>(mHeight) };

	if (clip != nullptr)
	{
		dstRect.w = clip->w;
		dstRect.h = clip->h;
	}

	if (width > 0)
	{
		dstRect.w = width;
	}

	if (height > 0)
	{
		dstRect.h = height;
	}

	SDL_RenderTextureRotated(renderer, mTexture, clip, &dstRect, degrees, center, flipMode);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}