#pragma once
/*---------------------------------------------A Sudoku Sudoku-------------------------------------------------*/
				// SDL Lazy Foo' Tutorials = https://lazyfoo.net/tutorials/SDL/index.php
				// SDL Documentation = https://wiki.libsdl.org/FrontPage
				// SDL True Type Fonts = https://www.libsdl.org/projects/SDL_ttf/

#include <SDL.h> 
#include <iostream>
#include <time.h>  

#include "Button.h"
#include "SudokuCell.h"
#include "SudokuGenerator.h"

namespace Sudoku
{
	class Sudoku
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

		// Define window and renderer
		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

		// Texture cache to hold preloaded textures
		int mTotalTextures;
		SDL_Texture* mTextureCache[14];

		// Define true type font paramaters
		TTF_Font* mFont;
		int mFontSize;

		// Define total buttons
		const int mTotalCells;

		// Define grid of cells (normally set to 9 x 9 = 81)
		Cell mGrid[81];

		// Define check and new buttons
		Button mCheckButton;
		Button mNewButton;

		// Timer
		Button mTimer;

		// Define colours 
		SDL_Color mClearColour;

	private:
		// Intialise SDL window, renderer and true type font
		bool initialiseSDL();

		// Get index of 1D array from row and col
		inline int getIndex(int row, int col) const;

		// Load textures using SDL true type fonts
		void loadTexture(SDL_Texture*& texture, const char* text, SDL_Color& fontColour);

		// Preload textures using SDL true type fonts
		void preloadTextures();

		// Create interface layout by setting button parameters
		void createInterfaceLayout();
		
		// Generate a Sudoku puzzle with a unique solution
		void generateSudoku();

		// Free textures
		void freeTextures();

	public:
		// Constructor to intialise member variables
		Sudoku();

		// Destructor to free textures
		~Sudoku();

	public:
		// Play Sudoku
		void play();

		// Close Sudoku
		void close();

	};

};