#pragma once
#include <SDL.h> 

class SudokuGrid
{
private:
	SDL_Renderer* Renderer;
	int Width;
	int Height;

public:
	SudokuGrid(SDL_Renderer* inputRenderer = NULL, int inputWidth = 100, int inputHeight = 100);
	void renderVerticalLines();
	void renderHorizontalLines();
	void render(SDL_Color& GridColour);

};