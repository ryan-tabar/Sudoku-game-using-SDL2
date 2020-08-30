#pragma once
#include <SDL.h> 
#include <SDL_image.h>
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
	LTexture(SDL_Renderer* inputRenderer = nullptr);

	// Deallocates memory
	~LTexture();

	// Set SDL_Rect
	void setTextureRect(SDL_Rect& inputRect);

	// Get SDL_Rect
	SDL_Rect getTextureRect();

	// Loads image from specified path
	bool loadFromFile(std::string& path);

	// Create image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColour, TTF_Font* Font);

	// Deallocates texture
	void free();

	// Renders texture at given point
	void renderTexture();

	// Gets image dimensions
	int getWidth();
	int getHeight();

	// Get renderer
	SDL_Renderer* getRenderer();

};