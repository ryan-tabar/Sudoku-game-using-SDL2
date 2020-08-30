#pragma once
#include <SDL.h> 
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

// Initialise subsystems, window and renderer
bool Init(SDL_Window*& Window, SDL_Renderer*& Renderer, TTF_Font*& Font, int FontSize, int SCREEN_WIDTH, int SCREEN_HEIGHT);

// Destroy and quit
void Close(SDL_Window*& Window, SDL_Renderer*& Renderer, TTF_Font*& Font);