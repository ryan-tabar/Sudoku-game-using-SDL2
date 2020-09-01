/* Sudoku generator and solver */
#include <SDL.h> 
#include <SDL_ttf.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "SudokuInit.h"
#include "LTexture.h"
#include "LMouse.h"
#include "SudokuGenerator.h"
#include "SudokuSolver.h"

// SDL Lazy Foo' Tutorials = https://lazyfoo.net/tutorials/SDL/index.php
// SDL Documentation = https://wiki.libsdl.org/FrontPage
// SDL True Type Fonts = https://www.libsdl.org/projects/SDL_ttf/

inline int getIndex(int row, int col, int gridRows)
{
	return row * gridRows + col;
}

inline bool isInteger(const char* s)
{
	// Returns true if s is an integer and greater than 0
	if (atoi(s)) return true;
	return false;
}

int main(int argc, char* argv[])
{
	// Define window dimensions
	const int WindowHeight = 900;
	const int WindowWidth = 810;

	// Define Sudoku screen dimensions
	const int ScreenHeight = 810;
	const int ScreenWidth = 810;

	// Define Sudoku grid rows and columns (normally set to 9 x 9)
	const int GridRows = 9;
	const int GridCols = 9;
	
	// Initialise window and renderer
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;

	// Intialise font for SDL true type fonts
	TTF_Font* Font = nullptr;
	int FontSize = ScreenHeight/GridRows;

	// Initialise SDL window, renderer and true type font
	if (!Init(Window, Renderer, Font, FontSize, WindowWidth, WindowHeight))
	{
		// If initialisation failed, then close and return
		Close(Window, Renderer, Font);
		return 1;
	}

	// Initialise colours (RGBA)
	SDL_Color ClearColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // Black
	SDL_Color GridColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // Black
	SDL_Color FontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // Black
	SDL_Color FixedButtonColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple

	// Generate Unique Sudoku array
	int generatedSudoku[GridRows * GridCols];
	SudokuGenerator SG;
	SG.setSudoku(generatedSudoku);
	SG.generateSudoku();

	// Create array of buttons
	const int TotalButtons = GridRows * GridCols;
	LButton Buttons[TotalButtons];

	// Define Button dimensions
	const int ButtonWidth = ScreenWidth / GridCols;
	const int ButtonHeight = ScreenHeight / GridRows;

	// Create offsets for grid display
	const float BorderFactor = 0.01;
	const float ThinBorderFactor = 0.5;
	const float ButtonStartOffSetFactor = 0.33;
	int ButtonStartWidthOffSet;
	int ButtonStartHeightOffSet;
	int ButtonWidthOffSet;
	int ButtonHeightOffSet;
	const int TextureWidthOffSet = FontSize / 5;
	const int TextureHeightOffSet = FontSize / 10;

	// Initialise button size and placement on the Sudoku grid.
	for (int row = 0; row < GridRows; row++)
	{
		for (int col = 0; col < GridCols; col++)
		{
			int currentIndex = getIndex(row, col, GridRows);
			Buttons[currentIndex].setRenderer(Renderer);

			// If statements for thicker borders on each 3 x 3 block
			if ((col + 1) % 3 == 0 && (col + 1) != GridCols) ButtonWidthOffSet = BorderFactor * ScreenWidth;
			else ButtonWidthOffSet = BorderFactor * ScreenWidth * ThinBorderFactor;

			if ((row + 1) % 3 == 0 && (row + 1) != GridRows) ButtonHeightOffSet = BorderFactor * ScreenHeight;
			else ButtonHeightOffSet = BorderFactor * ScreenHeight * ThinBorderFactor;

			ButtonStartWidthOffSet = ButtonWidthOffSet * ButtonStartOffSetFactor;
			ButtonStartHeightOffSet = ButtonWidthOffSet * ButtonStartOffSetFactor;

			Buttons[currentIndex].setButtonRect({ col * ButtonWidth + ButtonStartWidthOffSet, row * ButtonHeight + ButtonStartHeightOffSet, ButtonWidth - ButtonWidthOffSet, ButtonHeight - ButtonHeightOffSet });
			Buttons[currentIndex].setTextureRect({ col * ButtonWidth + TextureWidthOffSet, row * ButtonHeight + TextureHeightOffSet, NULL, NULL });

			std::string StringNum = std::to_string(SG.getElement(row, col));
			if (StringNum == "0")
			{
				StringNum = " ";
				Buttons[currentIndex].setEditable(true);
			}
			Buttons[currentIndex].setNumber(StringNum);
			Buttons[currentIndex].loadFromRenderedText(StringNum, FontColour, Font);

		}
	}

	// Solve Sudoku
	int solvedSudoku[GridRows * GridCols];
	SudokuSolver SS;
	SS.setSudoku(generatedSudoku);
	SS.solveSudoku();
	SS.displaySudoku();

	// Enable text input
	SDL_StartTextInput();

	// Set first current button selected
	LButton* currentButtonSelected = nullptr;
	for (int i = 0; i < TotalButtons; i++)
	{
		if (Buttons[i].getEditable())
		{
			currentButtonSelected = &Buttons[i];
			Buttons[i].setSelected(true);
			break;
		}
	}

	// Loop variables
	SDL_Event Event;
	bool Stop = false;
	bool UpdateTexture = false;
	std::string StringNum = "";
	bool Completed = false;

	while (!Stop)
	{
		// Update texture flag
		UpdateTexture = false;

		// Handle events on queue
		while (SDL_PollEvent(&Event) != 0)
		{
			// Handle quiting
			if (Event.type == SDL_QUIT || Completed == true)
			{
				Stop = true;
			}
			// Handle button events from mouse
			for (int i = 0; i < TotalButtons; i++)
			{
				// If editable
				if (Buttons[i].getEditable())
				{
					// Change the current button selected if a different button has been selected
					Buttons[i].handleEvent(&Event, currentButtonSelected);
				}
			}
			// Grab current number from selected button for checking
			StringNum = currentButtonSelected->getNumber();
			// Special key input
			if (Event.type == SDL_KEYDOWN)
			{
				// Handle backspace
				if (Event.key.keysym.sym == SDLK_BACKSPACE && StringNum.length() > 0)
				{
					// Pop off character
					StringNum.pop_back();
					currentButtonSelected->setNumber(StringNum);
					UpdateTexture = true;
				}
			}
			// Special text input event
			else if (Event.type == SDL_TEXTINPUT)
			{
				// Check if length is less than 1 and is a number
				if (isInteger(Event.text.text) && StringNum.length() < 2)
				{
					// Assign/replace character
					StringNum = Event.text.text;
					currentButtonSelected->setNumber(StringNum);
					UpdateTexture = true;
				}
			}
		}
		// Update texture if key pressed
		if (UpdateTexture)
		{
			// Text is not empty
			if (StringNum != "")
			{
				// Render new text
				currentButtonSelected->loadFromRenderedText(StringNum, FontColour, Font);
			}
			// Text is empty
			else
			{
				// Render an empty space texture
				currentButtonSelected->loadFromRenderedText(" ", FontColour, Font);
			}
		}

		// Check if complete
		for (int i = 0; i < TotalButtons; i++)
		{
			if (atoi(Buttons[i].getNumber().c_str()) != generatedSudoku[i])
			{
				Completed = false;
				break;
			}
			Completed = true;
		}

		// Clear screen
		SDL_SetRenderDrawColor(Renderer, ClearColour.r, ClearColour.g, ClearColour.b, ClearColour.a);
		SDL_RenderClear(Renderer);

		// Render buttons and texture to backbuffer
		for (int i = 0; i < TotalButtons; i++)
		{
			Buttons[i].renderButton();
			Buttons[i].renderTexture();
		}

		// Update screen from backbuffer and clear backbuffer
		SDL_RenderPresent(Renderer);

		// Slow down program becuase it does not need to run very fast
		SDL_Delay(10);
	}

	// Disable text input
	SDL_StopTextInput();

	// Display whether they completed successfully or closed before completing
	if (Completed)
	{
		std::cout << "Congratulations! You successfully completed the Sudoku puzzle!" << std::endl;
	}
	else
	{
		std::cout << "Oh no! You closed before completing the Sudoku puzzle!" << std::endl;
	}

	// Free button textures
	for (int i = 0; i < TotalButtons; ++i)
	{
		Buttons[i].free();
	}

	// Destroy and quit
	Close(Window, Renderer, Font);

	// Return succesfuly closing of program
	return 0;
}
