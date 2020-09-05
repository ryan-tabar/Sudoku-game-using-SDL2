#include "SudokuCell.h"

SudokuCell::SudokuCell()
	: mRenderer(nullptr),
	  mTexture(nullptr),
	  mFont(nullptr), 
	  mFontColour({0, 0, 0, SDL_ALPHA_OPAQUE }),
	  mCurrentState(ButtonState::BUTTON_MOUSE_OUT),
	  mButtonRect({0, 0, 0, 0}), 
	  mTextureRect({0, 0, 0, 0}),
	  mMouseOutColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mMouseOverMotionColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mMouseDownColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mMouseUpColour({ 159, 101, 152, SDL_ALPHA_OPAQUE }),
	  mEditable(false),
	  mSelected(false),
	  mNumber(0), 
	  mCharNumber(' '),
	  mSolution(0)
{

}

SudokuCell::~SudokuCell()
{
	freeTexture();
}

void SudokuCell::setNumber(const int number)
{
	mNumber = number;
	if (number == 0)
	{
		mCharNumber = ' ';
		setEditable(true);
	}
	else
	{
		mCharNumber = '0' + number;
	}
}

int SudokuCell::getNumber() const
{
	return mNumber;
}

void SudokuCell::setNumber(const char charNumber)
{
	mNumber = int(charNumber) - 48;
	mCharNumber = charNumber;
}

char SudokuCell::getCharNumber() const
{
	return mCharNumber;
}

void SudokuCell::setSolution(const int solution)
{
	mSolution = solution;
}

void SudokuCell::setRenderer(SDL_Renderer* const renderer)
{
	mRenderer = renderer;
}

void SudokuCell::setFont(TTF_Font* font)
{
	mFont = font;
}

void SudokuCell::setButtonRect(const SDL_Rect& const rect)
{
	mButtonRect = rect;
}

void SudokuCell::setTextureRect(const SDL_Rect& const rect)
{
	mTextureRect = rect;
}

void SudokuCell::setEditable(const bool editable)
{
	mEditable = editable;
	if (mEditable)
	{
		mMouseOutColour = { 219, 184, 215, SDL_ALPHA_OPAQUE }; // light purple
		mMouseOverMotionColour = { 95, 89, 191, SDL_ALPHA_OPAQUE }; // blue
		mMouseDownColour = { 91, 191, 116, SDL_ALPHA_OPAQUE }; // green
		mMouseUpColour = { 180, 48, 4, SDL_ALPHA_OPAQUE }; // red
	}
	else
	{
		mMouseOutColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
		mMouseOverMotionColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
		mMouseDownColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
		mMouseUpColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
	}
}

bool SudokuCell::isEditable() const
{
	return mEditable;
}

void SudokuCell::loadFontTexture()
{
	// Get rid of prexisting texture
	freeTexture();

	// Create text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, &mCharNumber, mFontColour);
	if (textSurface == nullptr)
	{
		std::cout << "Could not create TTF SDL_Surface! Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
		if (mTexture == nullptr)
		{
			std::cout << "Could not create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Get image dimensions
			SDL_QueryTexture(mTexture, NULL, NULL, &mTextureRect.w, &mTextureRect.h);
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
}

void SudokuCell::setSelected(const bool selected)
{
	mSelected = selected;
}

void SudokuCell::handleMouseEvent(const SDL_Event* const event, SudokuCell*& currentCellSelected)
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
				currentCellSelected->setSelected(false);
				// Set this.mSelected to true
				mSelected = true;
				// Set "this" as the current button selected
				currentCellSelected = this;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentState = ButtonState::BUTTON_MOUSE_UP;
				break;

			}
		}
	}
}

void SudokuCell::handleKeyboardEvent(const SDL_Event* const event)
{
	if (event->type == SDL_KEYDOWN)
	{
		// Handle backspace
		if (event->key.keysym.sym == SDLK_BACKSPACE && mCharNumber != ' ')
		{
			// Empty char
			mCharNumber = ' ';
			loadFontTexture();
		}
	}
	// Special text input event
	else if (event->type == SDL_TEXTINPUT)
	{
		// Check if integer > 0
		if (atoi(event->text.text))
		{
			// Replace char
			mCharNumber = *(event->text.text);
			loadFontTexture();
		}
	}
}

bool SudokuCell::isCorrect() const
{
	return mNumber == mSolution;
}

void SudokuCell::renderButton()
{
	// If current button is selected
	if (mSelected)
	{
		SDL_SetRenderDrawColor(mRenderer, mMouseDownColour.r, mMouseDownColour.g, mMouseDownColour.b, mMouseDownColour.a);
	}
	else
	{
		// Show current button State
		switch (mCurrentState)
		{
		case ButtonState::BUTTON_MOUSE_OUT:
			SDL_SetRenderDrawColor(mRenderer, mMouseOutColour.r, mMouseOutColour.g, mMouseOutColour.b, mMouseOutColour.a);
			break;

		case ButtonState::BUTTON_MOUSE_OVER_MOTION:
			SDL_SetRenderDrawColor(mRenderer, mMouseOverMotionColour.r, mMouseOverMotionColour.g, mMouseOverMotionColour.b, mMouseOverMotionColour.a);
			break;

		case ButtonState::BUTTON_MOUSE_UP:
			SDL_SetRenderDrawColor(mRenderer, mMouseUpColour.r, mMouseUpColour.g, mMouseUpColour.b, mMouseUpColour.a);
			break;

		}
	}

	SDL_RenderFillRect(mRenderer, &mButtonRect);
}

void SudokuCell::renderTexture()
{
	// Set rendering space and render to screen
	SDL_RenderCopy(mRenderer, mTexture, nullptr, &mTextureRect);
}

void SudokuCell::freeTexture()
{
	// Free texture if it exists
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
}

