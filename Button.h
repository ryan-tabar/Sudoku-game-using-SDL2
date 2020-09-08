/* A button class with colours and a texture*/
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

	// Define texture to display
	SDL_Texture* mTexture;

	// Top left position and dimensions of button and texture
	SDL_Rect mButtonRect;
	SDL_Rect mTextureRect;

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

	// Set Texture
	void setTexture(SDL_Texture* texture);

	// Set button and texture SDL_Rect
	void setButtonRect(const SDL_Rect& rect);
	void setTextureRect(const SDL_Rect& rect);

	// Center texture onto button
	void centerTextureRect();

	// Set selected
	void setSelected(const bool selected);

	// Check if mouse is inside button
	bool isMouseInside(const int x, const int y);
	
	// Get mouse event
	ButtonState getMouseEvent(const SDL_Event* event);

	// Set mouse down colour
	void setMouseDownColour(const SDL_Color& colour);

	// Render button and texture
	void renderButton(SDL_Renderer* renderer);
	void renderTexture(SDL_Renderer* renderer);

};