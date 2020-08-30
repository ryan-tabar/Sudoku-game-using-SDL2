#include "LTexture.h"

LTexture::LTexture(SDL_Renderer* inputRenderer)
	:mTexture(nullptr), mTextureRect({0, 0, 0, 0}), mRenderer(inputRenderer)
{

}

LTexture::~LTexture()
{
	// Deallocate
	free();
}

void LTexture::setTextureRect(SDL_Rect& inputRect)
{
    mTextureRect = inputRect;
}

SDL_Rect LTexture::getTextureRect()
{
	return mTextureRect;
}

bool LTexture::loadFromFile(std::string& path)
{
	// Get rid of preexisting texture
	free();

	// The final texture
	SDL_Texture* newTexture = nullptr;

	// Load image at specified path
	newTexture = IMG_LoadTexture(mRenderer, path.c_str());
	if (newTexture == nullptr)
	{
		std::cout << "Could not load texture! Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		// Get image dimensions
		SDL_QueryTexture(newTexture, NULL, NULL, &mTextureRect.w, &mTextureRect.w);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != nullptr;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColour, TTF_Font* Font)
{
	// Get rid of prexisting texture
	free();

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColour);
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

void LTexture::renderTexture()
{
	// Set rendering space and render to screen
	SDL_RenderCopy(mRenderer, mTexture, nullptr, &mTextureRect);
}

int LTexture::getWidth()
{
	return mTextureRect.w;
}

int LTexture::getHeight()
{
	return mTextureRect.h;
}

SDL_Renderer* LTexture::getRenderer()
{
	return mRenderer;
}

