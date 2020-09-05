#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h> // for atoi

#include "Button.h"
#include "Texture.h"

namespace Sudoku
{
	class Cell : public Button, public Texture
	{
	private:
		// Define editiability (can type number in cell)
		bool mEditable;

		// Define number currently displayed and the actual solution
		char mCharNumber;
		char mCharSolution;

	public:
		// Constructor
		Cell();

		// Set and get number
		void setNumber(const int number);
		char getNumber() const;

		// Set solution
		void setSolution(const int solution);

		// Set and get editability (setting editability changes colour mapping for button)
		void setEditable(const bool editable);
		bool isEditable() const;

		// Handle events
		void handleKeyboardEvent(const SDL_Event* const event, SDL_Renderer* renderer, TTF_Font* font);

		// Compare number with solution
		bool isCorrect() const;

	};

};