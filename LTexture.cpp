#include "LTexture.h"

LTexture::LTexture()
	:mTexture(nullptr), mTextureRect({0, 0, 0, 0}), mRenderer(nullptr)
{

}

LTexture::~LTexture()
{
	// Deallocate
	free();
}

void LTexture::setRenderer(SDL_Renderer* const inputRenderer)
{
	mRenderer = inputRenderer;
}

SDL_Renderer* LTexture::getRenderer() const
{
	return mRenderer;
}

void LTexture::setTextureRect(const SDL_Rect& const inputRect)
{
    mTextureRect = inputRect;
}

SDL_Rect LTexture::getTextureRect() const
{
	return mTextureRect;
}

bool LTexture::loadFromRenderedText(const std::string& const textureText, const SDL_Color& const textColour, TTF_Font* const font)
{
	// Get rid of prexisting texture
	free();

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColour);
	if (textSurface == nullptr)
	{
		std::cout << "Could not create TTF SDL_Surface! Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
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
	
	//Return success
	return mTexture != nullptr;
}

void LTexture::free()
{
	// Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}

void LTexture::renderTexture() const
{
	// Set rendering space and render to screen
	SDL_RenderCopy(mRenderer, mTexture, nullptr, &mTextureRect);
}

