#include <SDL.h> 
#include <SDL_image.h>
#include <iostream>
#include "CleanUp.h"
#include "SudokuGrid.h"

constexpr int SCREEN_WIDTH = 810;
constexpr int SCREEN_HEIGHT = 810;

int main(int argc, char* argv[])
{
	// Initalise video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_init" << " error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	// Create window
	SDL_Window* Window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == nullptr)
	{
		std::cout << "SDL_CreateWindow" << " error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// Create renderer
	SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer" << " error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	// Grid colours
	SDL_Color ClearColour = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	SDL_Color GridColour = { 0, 0, 0, SDL_ALPHA_OPAQUE };

	// Loop variables
	bool Quit = false;
	SDL_Event E;

	while (!Quit)
	{
		/*----------------------------Handle events on queue----------------------------*/
		while (SDL_PollEvent(&E) != 0)
		{
			// User requests quit
			if (E.type == SDL_QUIT)
			{
				Quit = true;
			}
		}
		/*----------------------------Creating a Sudoku grid----------------------------*/
		SudokuGrid S_Grid(Renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		S_Grid.ClearRenderer(ClearColour);
		S_Grid.DrawGrid(GridColour);
		S_Grid.UpdateGrid();
		/*------------------------------------------------------------------------------*/
		

	}

	// Cleaning Up
	CleanUp(Window, Renderer); // surface gets cleared up with window
	SDL_Quit();

	return 0;
}
