#include "Texture.h"

Texture::Texture()
	: mTexture(nullptr),
	  mFontColour({ 0, 0, 0, SDL_ALPHA_OPAQUE }),
	  mTextureRect({ 0, 0, 0, 0 })
{

}

Texture::~Texture()
{
	freeTexture();
}

void Texture::setTextureRect(const SDL_Rect& const rect)
{
	mTextureRect = rect;
}


void Texture::loadFontTexture(SDL_Renderer* renderer, TTF_Font* font, const char text)
{
	// Get rid of prexisting texture
	freeTexture();

	// Create text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, &text, mFontColour);
	if (textSurface == nullptr)
	{
		std::cout << "Could not create TTF SDL_Surface! Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == nullptr)
		{
			std::cout << "Could not create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Get image dimensions
			SDL_QueryTexture(mTexture, NULL, NULL, &mTextureRect.w, &mTextureRect.h);
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}

void Texture::renderTexture(SDL_Renderer* renderer)
{
	// Set rendering space
	SDL_RenderCopy(renderer, mTexture, nullptr, &mTextureRect);
}

void Texture::freeTexture()
{
	// Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}
