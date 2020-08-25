//https://www.willusher.io/sdl2%20tutorials/2013/08/17/lesson-2-dont-put-everything-in-main
//http://lazyfoo.net/tutorials/SDL/index.php

#include <SDL.h> 
#include <iostream>
#include <string>
#include "res_path.h"
#include "cleanup.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream& os, const std::string &msg)
{
	os << msg << " error:" << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* loadedImage = SDL_LoadBMP(file.c_str());
	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		if (texture == nullptr)
		{
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else
	{
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;

}

int main(int argc, char* argv[])
{
	// Initalise video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}
	
	// Openning a Window
	SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		logSDLError(std::cout, "SDL_CreateWindow");
		SDL_Quit();
		return 1;
	}

	// Creating a Renderer
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		cleanup(win);
		logSDLError(std::cout, "SDL_CreateRender");
		SDL_Quit();
		return 1;
	}

	// Loading a Bitmap Image
	std::string imagePath = getResourcePath("Lesson1") + "hello.bmp";
	std::cout << imagePath << std::endl;
	SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr)
	{
		cleanup(ren, win);
		logSDLError(std::cout, "SDL_LoadBMP");
		SDL_Quit();
		return 1;
	}

	// Upload Bitmap Image to renderer
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr)
	{
		cleanup(ren, win);
		logSDLError(std::cout, "SDL_CreateTextureFromSurface");
		SDL_Quit();
		return 1;
	}

	// Drawing the Texture
	for (int i = 0; i < 3; ++i)
	{
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, tex, NULL, NULL);
		SDL_RenderPresent(ren);
		SDL_Delay(1000);
	}

	// Cleaning Up
	cleanup(tex, ren, win);
	SDL_Quit();

	return 0;
}
