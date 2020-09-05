#pragma once
#include <SDL.h>

enum class ButtonState
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER_MOTION = 1,
	BUTTON_MOUSE_DOWN = 2,
	BUTTON_MOUSE_UP = 3,
};

class Button
{

private:
	// Current button state
	ButtonState mCurrentState;

	// Top left position and dimensions of button
	SDL_Rect mButtonRect;

	// Has the button been selected by the mouse
	bool mSelected;

protected:
	// Define button colours
	SDL_Color mMouseOutColour;
	SDL_Color mMouseOverMotionColour;
	SDL_Color mMouseDownColour;
	SDL_Color mMouseUpColour;

public:
	// Constructor
	Button();

	// Set button SDL_Rect
	void setButtonRect(const SDL_Rect& const rect);

	// Set selected
	void setSelected(const bool selected);

	// Handle events
	void handleMouseEvent(const SDL_Event* const event, Button*& currentButtonSelected);

	// Render button and texture
	void renderButton(SDL_Renderer* renderer);

};