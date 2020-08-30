/* Sudoku program */
#include <SDL.h> 
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>

#include "SudokuInit.h"
#include "SudokuGrid.h"
#include "LTexture.h"
#include "LMouse.h"

// SDL Lazy Foo' Tutorials = https://lazyfoo.net/tutorials/SDL/index.php
// SDL Documentation = https://wiki.libsdl.org/FrontPage
// SDL Image Documentation = https://www.libsdl.org/projects/SDL_image/docs/index.html
// SDL True Type Fonts = https://www.libsdl.org/projects/SDL_ttf/

inline bool isInteger(const std::string& s)
{	
	// Returns true if s is an integer greater than 0
	if (atoi(s.c_str())) return true;
	return false;
}

inline int getIndex(int row, int col)
{
	return row * 9 + col;
}

inline void getRenderCoordinates(int row, int col, int* posX, int* posY, int FontSize)
{
	*posX = (int)(FontSize * col + FontSize/5);
	*posY = (int)(FontSize * row + FontSize/9);
}

int main(int argc, char* argv[])
{
	// Define window dimensions
	constexpr int SCREEN_HEIGHT = 810;
	constexpr int SCREEN_WIDTH = 810;

	// Initialise window and renderer
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;

	// Intialise font
	TTF_Font* Font = nullptr;
	int FontSize = SCREEN_HEIGHT/9;

	// Initialise colours (RGBA)
	SDL_Color ClearColour = { 255, 255, 255, SDL_ALPHA_OPAQUE };
	SDL_Color GridColour = { 0, 0, 0, SDL_ALPHA_OPAQUE };
	SDL_Color FontColour = { 0, 0, 0, SDL_ALPHA_OPAQUE };

	// Initialise subsystems
	if (!Init(Window, Renderer, Font, FontSize, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		Close(Window, Renderer, Font);
		return 1;
	}

	// Creating Sudoku grid
	SudokuGrid S_Grid(Renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Clear screen
	SDL_SetRenderDrawColor(Renderer, ClearColour.r, ClearColour.g, ClearColour.b, ClearColour.a);
	SDL_RenderClear(Renderer);

	// Render
	S_Grid.render(GridColour);
	SDL_RenderPresent(Renderer);

	// Create array of text inputs for numbers (9 x 9 = 81)
	int TOTAL_BUTTONS = 81;
	std::vector<LButton> InputNumberButtons;
	int ButtonWidth = SCREEN_WIDTH / 9;
	int ButtonHeight = SCREEN_HEIGHT / 9;
	int WidthOffSet = FontSize / 5;
	int HeightOffSet = FontSize / 9;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			SDL_Rect ButtonRect = {col*ButtonWidth, row*ButtonHeight, ButtonWidth, ButtonHeight};
			SDL_Rect TextureRect = {col*ButtonWidth + WidthOffSet, row*ButtonHeight + HeightOffSet, NULL, NULL};
			LButton InputButton(Renderer);
			InputButton.setButtonRect(ButtonRect);
			InputButton.setTextureRect(TextureRect);
			InputNumberButtons.push_back(InputButton);
		}
	}

	// Enable text input
	SDL_StartTextInput();
	LButton Num(Renderer);

	// Loop variables
	LButton* currentButtonSelected = nullptr;
	bool Stop = false;
	SDL_Event E;

	while (!Stop)
	{

		// Rerender text
		bool RenderText = false;

		/// Handle events on queue
		while (SDL_PollEvent(&E) != 0)
		{
			// User requests quit
			if (E.type == SDL_QUIT)
			{
				Stop = true;
			}
			// Handle button events
			for (int i = 0; i < TOTAL_BUTTONS; i++)
			{
				// Check if button is selected
				InputNumberButtons[i].handleEvent(&E, currentButtonSelected);
				if (InputNumberButtons[i].isSelected())
				{
					currentButtonSelected = &InputNumberButtons[i];
				}

			}
			if (currentButtonSelected != nullptr)
			{
				std::string StringNum = currentButtonSelected->getNumber();
				// Special key input
				if (E.type == SDL_KEYDOWN)
				{
					// Handle backspace
					if (E.key.keysym.sym == SDLK_BACKSPACE && StringNum.length() > 0)
					{
						// Pop off character
						StringNum.pop_back();
						currentButtonSelected->setNumber(StringNum);
						RenderText = true;
					}
				}
				// Special text input event
				else if (E.type == SDL_TEXTINPUT)
				{
					// Check if length is less than 1 and is a number
					if (isInteger(E.text.text) && StringNum.length() < 1)
					{
						// Append character
						StringNum += E.text.text;
						currentButtonSelected->setNumber(StringNum);
						RenderText = true;
					}
				}
			}
		}

		// Render each button text texture
		for (int i = 0; i < TOTAL_BUTTONS; i++)
		{
			std::string StringNum = InputNumberButtons[i].getNumber();
			// Text is not empty
			if (StringNum != "")
			{
				// Render new text
				InputNumberButtons[i].loadFromRenderedText(StringNum, FontColour, Font);
			}
			// Text is empty
			else
			{
				// Render space texture
				InputNumberButtons[i].loadFromRenderedText(" ", FontColour, Font);
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(Renderer, ClearColour.r, ClearColour.g, ClearColour.b, ClearColour.a);
		SDL_RenderClear(Renderer);

		// Render buttons and texture
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			InputNumberButtons[i].renderButton();
			InputNumberButtons[i].renderTexture();
		}

		// Render grid
		S_Grid.render(GridColour);

		// Update screen
		SDL_RenderPresent(Renderer);
	}

	// Disable text input
	SDL_StopTextInput();

	// Free input button textures
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		InputNumberButtons[i].free();
	}

	// Destroy and quit
	Close(Window, Renderer, Font);

	// Return succesfuly closing of program
	return 0;
}
