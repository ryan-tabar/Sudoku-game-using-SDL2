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
	void ClearRenderer(SDL_Color& ClearColour);
	void DrawVerticalLines();
	void DrawHorizontalLines();
	void DrawGrid(SDL_Color& GridColour);
	void UpdateGrid();

};