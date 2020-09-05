#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

class Texture
{
private:
	// The actual hardware texture for displaying SDL true type font
	SDL_Texture* mTexture;

	// Define font colour
	SDL_Color mFontColour;

	// Top left position and dimensions texture
	SDL_Rect mTextureRect;

public:
	// Constructor
	Texture();

	// Destructor to free textures
	~Texture();

	// Set button SDL_Rect;
	void setTextureRect(const SDL_Rect& const rect);

	// Load texture
	void loadFontTexture(SDL_Renderer* renderer, TTF_Font* font, const char text);

	// Render texture
	void renderTexture(SDL_Renderer* renderer);

	// Free texture
	void freeTexture();

};