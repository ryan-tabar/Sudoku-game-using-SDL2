/* Sudoku program */
#include <SDL.h> 
#include <SDL_ttf.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "SudokuInit.h"
#include "LTexture.h"
#include "LMouse.h"

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

	// Initialise colours (RGBA)
	SDL_Color ClearColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // Black
	SDL_Color GridColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // Black
	SDL_Color FontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE }; // Black

	// Initialise window, renderer and true type font
	if (!Init(Window, Renderer, Font, FontSize, ScreenWidth, ScreenHeight))
	{
		// If initialisation failed, then close and return
		Close(Window, Renderer, Font);
		return 1;
	}

	// Create array of buttons
	const int TotalButtons = GridRows * GridCols;
	LButton Buttons[TotalButtons];

	// Define Button dimensions
	const int ButtonWidth = ScreenWidth / GridCols;
	const int ButtonHeight = ScreenHeight / GridRows;

	// Create offsets for texture for number display to center it
	const int WidthOffSet = FontSize / 5;
	const int HeightOffSet = FontSize / 9;

	// Initialise each button of the sudoku grid
	for (int row = 0; row < GridRows; row++)
	{
		for (int col = 0; col < GridCols; col++)
		{
			int currentIndex = getIndex(row, col, GridRows);
			Buttons[currentIndex].setRenderer(Renderer);
			SDL_Rect ButtonRect = {col*ButtonWidth+10, row*ButtonHeight+10, ButtonWidth-10, ButtonHeight-10};
			SDL_Rect TextureRect = {col*ButtonWidth + WidthOffSet, row*ButtonHeight + HeightOffSet, NULL, NULL};
			Buttons[currentIndex].setButtonRect(ButtonRect);
			Buttons[currentIndex].setTextureRect(TextureRect);
		}
	}

	// Enable text input
	SDL_StartTextInput();

	// Loop variables
	SDL_Event Event;
	LButton* currentButtonSelected = &Buttons[0];
	bool Stop = false;
	bool UpdateTexture = false;
	std::string StringNum = "";

	while (!Stop)
	{
		// Update text
		UpdateTexture = false;

		/// Handle events on queue
		while (SDL_PollEvent(&Event) != 0)
		{
			// Handle quiting
			if (Event.type == SDL_QUIT)
			{
				Stop = true;
			}
			// Handle button events from mouse
			for (int i = 0; i < TotalButtons; i++)
			{
				// Change the current button selected if a different button has been selected
				Buttons[i].handleEvent(&Event, currentButtonSelected);
			}
			// Handle key inputs
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
				if (isInteger(Event.text.text) && StringNum.length() < 1)
				{
					// Append character
					StringNum += Event.text.text;
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
	}

	// Disable text input
	SDL_StopTextInput();

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
