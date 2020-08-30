#include "SudokuInit.h"

// Initialise subsystems, window and renderer
bool Init(SDL_Window*& Window, SDL_Renderer*& Renderer, TTF_Font*& Font, int FontSize, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	// Set success initialisation flag
	bool success = true;

	// Initalise SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL could not intialise! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Initialise SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialise! Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	// Create window
	Window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == nullptr)
	{
		std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Create renderer
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == nullptr)
	{
		std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Load font for text
	Font = TTF_OpenFont("Resources/VALENTIN.TTF", FontSize);
	if (Font == nullptr)
	{
		std::cout << "Failed to load lazy font! Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	return success;
}

// Destroy and quit
void Close(SDL_Window*& Window, SDL_Renderer*& Renderer, TTF_Font*& Font)
{
	// Destroy
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Renderer = nullptr;
	Window = nullptr;

	// Free global font
	TTF_CloseFont(Font);
	Font = nullptr;

	// Quit
	SDL_Quit();
	TTF_Quit();
}