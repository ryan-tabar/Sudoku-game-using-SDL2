#pragma once
#include <SDL.h> 
#include <SDL_ttf.h>
#include <string>
#include <iostream>

// A wrapper for SDL_Texture
class LTexture
{
private:
	// The actual hardware texture
	SDL_Texture* mTexture;

	// Image dimensions and top left position
	SDL_Rect mTextureRect;

	// The renderer
	SDL_Renderer* mRenderer;

public:
	// Intialise variables
	LTexture();

	// Deallocates memory
	~LTexture();

	// Set renderer
	void setRenderer(SDL_Renderer* const inputRenderer);
	
	// Get renderer
	SDL_Renderer* getRenderer() const;

	// Set SDL_Rect
	void setTextureRect(const SDL_Rect& const inputRect);

	// Get SDL_Rect
	SDL_Rect getTextureRect() const;

	// Create image from font string
	bool loadFromRenderedText(const std::string& const textureText, const SDL_Color& const textColour, TTF_Font* const font);

	// Deallocates texture
	void free();

	// Renders texture at given point
	void renderTexture() const;

};