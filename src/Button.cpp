#include "Button.h"

Button::Button()
	: mCurrentState(ButtonState::BUTTON_MOUSE_OUT),
	  mTexture(nullptr),
	  mButtonRect({ 0, 0, 0, 0 }),
	  mTextureRect({0, 0, 0, 0}),
	  mMouseOutColour({ 219, 184, 215, SDL_ALPHA_OPAQUE }), // light purple
	  mMouseOverMotionColour({ 95, 89, 191, SDL_ALPHA_OPAQUE }),//blue
	  mMouseDownColour({ 91, 191, 116, SDL_ALPHA_OPAQUE }), // green
	  mMouseUpColour({ 95, 89, 191, SDL_ALPHA_OPAQUE }), // blue
	  mSelected(false)
{

}

void Button::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
}

void Button::setButtonRect(const SDL_Rect& rect)
{
	mButtonRect = rect;
}

void Button::setTextureRect(const SDL_Rect& rect)
{
	mTextureRect = rect;
}

void Button::centerTextureRect()
{
	int textureWidth;
	int textureHeight;
	SDL_QueryTexture(mTexture, NULL, NULL, &textureWidth, &textureHeight);

	const int textureStartRow = mButtonRect.y + 0.5 * (mButtonRect.h - textureHeight);
	const int textureStartCol = mButtonRect.x + 0.5 * (mButtonRect.w - textureWidth);

	mTextureRect = { textureStartCol, textureStartRow, textureWidth, textureHeight };
}

void Button::setSelected(const bool selected)
{
	mSelected = selected;
}

bool Button::isMouseInside(const int x, const int y)
{
	// Check if mouse is in button
	bool inside = true;

	// Mouse is left of the button
	if (x < mButtonRect.x)
	{
		inside = false;
	}
	// Mouse is right of the button
	else if (x > mButtonRect.x + mButtonRect.w)
	{
		inside = false;
	}
	// Mouse above the button
	else if (y < mButtonRect.y)
	{
		inside = false;
	}
	// Mouse below the button
	else if (y > mButtonRect.y + mButtonRect.h)
	{
		inside = false;
	}

	return inside;
}

ButtonState Button::getMouseEvent(const SDL_Event* event)
{
	//If mouse event happened
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse is outside button
		if (!isMouseInside(x, y))
		{
			mCurrentState = ButtonState::BUTTON_MOUSE_OUT;
		}
		// Mouse is inside button
		else
		{
			// Set mouse over State
			switch (event->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentState = ButtonState::BUTTON_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentState = ButtonState::BUTTON_MOUSE_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentState = ButtonState::BUTTON_MOUSE_UP;
				break;

			}
		}
	}
	return mCurrentState;
}

void Button::setMouseDownColour(const SDL_Color& colour)
{
	mMouseDownColour = colour;
}

void Button::renderButton(SDL_Renderer* renderer)
{
	// If current button is selected
	if (mSelected)
	{
		SDL_SetRenderDrawColor(renderer, mMouseDownColour.r, mMouseDownColour.g, mMouseDownColour.b, mMouseDownColour.a);
	}
	else
	{
		// Show current button State
		switch (mCurrentState)
		{
		case ButtonState::BUTTON_MOUSE_OUT:
			SDL_SetRenderDrawColor(renderer, mMouseOutColour.r, mMouseOutColour.g, mMouseOutColour.b, mMouseOutColour.a);
			break;
		case ButtonState::BUTTON_MOUSE_OVER_MOTION:
			SDL_SetRenderDrawColor(renderer, mMouseOverMotionColour.r, mMouseOverMotionColour.g, mMouseOverMotionColour.b, mMouseOverMotionColour.a);
			break;
		case ButtonState::BUTTON_MOUSE_DOWN:
			SDL_SetRenderDrawColor(renderer, mMouseDownColour.r, mMouseDownColour.g, mMouseDownColour.b, mMouseDownColour.a);
			break;
		case ButtonState::BUTTON_MOUSE_UP:
			SDL_SetRenderDrawColor(renderer, mMouseUpColour.r, mMouseUpColour.g, mMouseUpColour.b, mMouseUpColour.a);
			break;

		}
	}

	SDL_RenderFillRect(renderer, &mButtonRect);
}

void Button::renderTexture(SDL_Renderer* renderer)
{
	// Set rendering space
	SDL_RenderCopy(renderer, mTexture, nullptr, &mTextureRect);
}

