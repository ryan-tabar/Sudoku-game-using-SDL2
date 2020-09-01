#include "LMouse.h"

LButton::LButton()
	:mCurrentState(LButtonState::BUTTON_MOUSE_OUT), mButtonRect({ 0, 0, 0, 0 }), 
    mSelected(false), mNumber(""), mEditable(false)
{

}

void LButton::setButtonRect(const SDL_Rect& const inputRect)
{
    mButtonRect = inputRect;
}

SDL_Rect LButton::getButtonRect() const
{
    return mButtonRect;
}

void LButton::setEditable(const bool input)
{
    mEditable = input;
    if (mEditable)
    {
        MouseOutColour = { 219, 184, 215, SDL_ALPHA_OPAQUE }; // light purple
        MouseOverMotionColour = { 95, 89, 191, SDL_ALPHA_OPAQUE }; // blue
        MouseDownColour = { 91, 191, 116, SDL_ALPHA_OPAQUE }; // green
        MouseUpColour = { 95, 89, 191, SDL_ALPHA_OPAQUE }; // blue
    }
    else
    {
        MouseOutColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
        MouseOverMotionColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
        MouseDownColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
        MouseUpColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
    }
}

bool LButton::getEditable()
{
    return mEditable;
}

void LButton::handleEvent(const SDL_Event* const Event, LButton*& currentButtonSelected)
{
    //If mouse event happened
    if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN || Event->type == SDL_MOUSEBUTTONUP)
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
            mCurrentState = LButtonState::BUTTON_MOUSE_OUT;
        }
        // Mouse is inside button
        else
        { 
            // Set mouse over State
            switch (Event->type)
            {
            case SDL_MOUSEMOTION:
                mCurrentState = LButtonState::BUTTON_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mCurrentState = LButtonState::BUTTON_MOUSE_DOWN;
                // check if this.mSelected is false
                if (mSelected == false)
                {
                    currentButtonSelected->setSelected(false);
                }
                // Set this.mSelected to true
                mSelected = true;
                // Set "this" as the current button selected
                currentButtonSelected = this;
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentState = LButtonState::BUTTON_MOUSE_UP;
                break;

            }
        }
    }
}

bool LButton::isSelected() const
{
    return mSelected;
}

void LButton::setSelected(bool input)
{
    mSelected = input;
}

void LButton::renderButton()
{
    // Initialise colours (RGBA)
    SDL_Renderer* dRenderer = getRenderer();

    // If current button is selected
    if (mSelected)
    {
        SDL_SetRenderDrawColor(dRenderer, MouseDownColour.r, MouseDownColour.g, MouseDownColour.b, MouseDownColour.a);
    }
    else
    {
        // Show current button State
        switch (mCurrentState)
        {
        case LButtonState::BUTTON_MOUSE_OUT:
            SDL_SetRenderDrawColor(dRenderer, MouseOutColour.r, MouseOutColour.g, MouseOutColour.b, MouseOutColour.a);
            break;

        case LButtonState::BUTTON_MOUSE_OVER_MOTION:
            SDL_SetRenderDrawColor(dRenderer, MouseOverMotionColour.r, MouseOverMotionColour.g, MouseOverMotionColour.b, MouseOverMotionColour.a);
            break;
    
        case LButtonState::BUTTON_MOUSE_UP:
            SDL_SetRenderDrawColor(dRenderer, MouseUpColour.r, MouseUpColour.g, MouseUpColour.b, MouseUpColour.a);
            break;

        }
    }
   
    SDL_RenderFillRect(dRenderer, &mButtonRect);
}

std::string LButton::getNumber() const
{
    return mNumber;
}

void LButton::setNumber(const std::string& const inputNumber)
{
    mNumber = inputNumber;
}
