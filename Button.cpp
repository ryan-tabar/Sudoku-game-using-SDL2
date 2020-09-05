#include "Button.h"

Button::Button()
	: mCurrentState(ButtonState::BUTTON_MOUSE_OUT),
	  mButtonRect({ 0, 0, 0, 0 }),
	  mMouseOutColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mMouseOverMotionColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mMouseDownColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mMouseUpColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mSelected(false)
{

}

void Button::setButtonRect(const SDL_Rect& const rect)
{
	mButtonRect = rect;
}

void Button::setSelected(const bool selected)
{
	mSelected = selected;
}

void Button::handleMouseEvent(const SDL_Event* const event, Button*& currentButtonSelected)
{
	//If mouse event happened
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

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

		// Mouse is outside button
		if (!inside)
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
				// Set current selected false
				currentButtonSelected->setSelected(false);
				// Set this.mSelected to true
				mSelected = true;
				// Set "this" as the current button selected
				currentButtonSelected = this;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentState = ButtonState::BUTTON_MOUSE_UP;
				break;

			}
		}
	}
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

		case ButtonState::BUTTON_MOUSE_UP:
			SDL_SetRenderDrawColor(renderer, mMouseUpColour.r, mMouseUpColour.g, mMouseUpColour.b, mMouseUpColour.a);
			break;

		}
	}

	SDL_RenderFillRect(renderer, &mButtonRect);
}

