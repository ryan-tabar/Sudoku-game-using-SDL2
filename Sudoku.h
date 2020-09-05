#pragma once
/*---------------------------------------------A Sudoku game-------------------------------------------------*/
				// SDL Lazy Foo' Tutorials = https://lazyfoo.net/tutorials/SDL/index.php
				// SDL Documentation = https://wiki.libsdl.org/FrontPage
				// SDL True Type Fonts = https://www.libsdl.org/projects/SDL_ttf/

#include <SDL.h> 
#include <iostream>

#include "SudokuCell.h"
#include "SudokuGenerator.h"

namespace Sudoku
{
	class Game
	{
	private:
		// Define window dimensions
		const int mWindowHeight;
		const int mWindowWidth;

		// Define Sudoku grid dimensions
		const int mGridHeight;
		const int mGridWidth;

		// Define Sudoku max grid rows and columns (normally set to 9 x 9)
		const int mGridRows;
		const int mGridCols;

		// Define total buttons
		const int mTotalCells;

		// Define grid of cells (normally set to 9 x 9 = 81)
		Cell mGrid[81];

		// Define window and renderer
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		// Define true type font paramaters
		TTF_Font* mFont;
		int mFontSize;

		// Define colours 
		SDL_Color mClearColour;

	private:
		// Intialise SDL window, renderer and true type font
		bool initialiseSDL();

		// Get index of ID array from row and col
		inline int getIndex(int row, int col) const;

		// Generate a Sudoku puzzle with a unique solution
		void generateSudoku();

		// Set cell button and texture paramaters based on generated Sudoku
		void setCells();

		// Free textures
		void freeTextures();

	public:
		// Constructor
		Game();

		// Destructor to free textures
		~Game();

	public:
		// Play Sudoku
		void play();

		// Close Sudoku
		void close();

	};

};