#include "SudokuGrid.h"

SudokuGrid::SudokuGrid(SDL_Renderer* inputRenderer, int inputWidth, int inputHeight)
	:Renderer(inputRenderer), Width(inputWidth), Height(inputHeight)
{

}

void SudokuGrid::ClearRenderer(SDL_Color& ClearColour)
{
	SDL_SetRenderDrawColor(Renderer, ClearColour.r, ClearColour.g, ClearColour.b, ClearColour.a);
	SDL_RenderClear(Renderer);
}

void SudokuGrid::DrawVerticalLines()
{
	for (int h_offset = 0; h_offset < Width; h_offset += Width / 9)
	{
		SDL_RenderDrawLine(Renderer, h_offset, 0, h_offset, Height);
	}
}

void SudokuGrid::DrawHorizontalLines()
{
	for (int v_offset = 0; v_offset < Width; v_offset += Width / 9)
	{
		SDL_RenderDrawLine(Renderer, 0, v_offset, Width, v_offset);
	}
}

void SudokuGrid::DrawGrid(SDL_Color& GridColour)
{
	SDL_SetRenderDrawColor(Renderer, GridColour.r, GridColour.g, GridColour.b, GridColour.a);
	DrawVerticalLines();
	DrawHorizontalLines();
}

void SudokuGrid::UpdateGrid()
{
	SDL_RenderPresent(Renderer);
}
