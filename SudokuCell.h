#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdlib.h> // for atoi

enum class ButtonState
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER_MOTION = 1,
	BUTTON_MOUSE_DOWN = 2,
	BUTTON_MOUSE_UP = 3,
};

class SudokuCell
{
private:
	// The renderer
	SDL_Renderer* mRenderer;

	// The actual hardware texture for displaying SDL true type font
	SDL_Texture* mTexture;

	// Define font parameters for displaying the number
	TTF_Font* mFont;
	SDL_Color mFontColour;

	// Currently mouse state
	ButtonState mCurrentState;

	// Top left position and dimensions of button and texture
	SDL_Rect mButtonRect;
	SDL_Rect mTextureRect;

	// Default Cell colours
	SDL_Color mMouseOutColour;
	SDL_Color mMouseOverMotionColour;
	SDL_Color mMouseDownColour;
	SDL_Color mMouseUpColour;

	// Define editiability (can type number in cell)
	bool mEditable;

	// Has the button been selected by the mouse
	bool mSelected;

	// Define number currently displayed and the actual solution
	int mNumber;
	char mCharNumber;
	int mSolution;

public:
	// Constructor
	SudokuCell();

	// Destructor to free textures
	~SudokuCell();

	// Set and get number
	void setNumber(const int number);
	int getNumber() const;

	// Set and get number in string format
	void setNumber(const char charNumber);
	char getCharNumber() const;

	// Set solution
	void setSolution(const int solution);

	// Set renderer for texture
	void setRenderer(SDL_Renderer* const renderer);

	// Set font
	void setFont(TTF_Font* font);

	// Set button and texture SDL_Rects
	void setButtonRect(const SDL_Rect& const rect);
	void setTextureRect(const SDL_Rect& const rect);

	// Set and get editability (setting editability changes colour mapping for button)
	void setEditable(const bool editable);
	bool isEditable() const;

	// Load texture
	void loadFontTexture();

	// Set selected
	void setSelected(const bool selected);

	// Handle events
	void handleMouseEvent(const SDL_Event* const event, SudokuCell*& currentCellSelected);
	void handleKeyboardEvent(const SDL_Event* const event);

	// Compare number with solution
	bool isCorrect() const;

	// Render button and texture
	void renderButton();
	void renderTexture();

	// Free texture
	void freeTexture();

};