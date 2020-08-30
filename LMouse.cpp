#include "LMouse.h"

LButton::LButton(SDL_Renderer* inputRenderer)
	:LTexture(inputRenderer), mCurrentState(LButtonState::BUTTON_MOUSE_OUT), mButtonRect({ 0, 0, 0, 0 }), mSelected(false), mNumber("")
{

}

void LButton::setButtonRect(SDL_Rect& inputRect)
{
    mButtonRect = inputRect;
}

SDL_Rect LButton::getButtonRect()
{
    return mButtonRect;
}

void LButton::handleEvent(SDL_Event* E, LButton* currentSelected)
{
    //If mouse event happened
    if (E->type == SDL_MOUSEMOTION || E->type == SDL_MOUSEBUTTONDOWN || E->type == SDL_MOUSEBUTTONUP)
    {
        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Get SDL_Rect from inherited class LTexture

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
            switch (E->type)
            {
            case SDL_MOUSEMOTION:
                mCurrentState = LButtonState::BUTTON_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mCurrentState = LButtonState::BUTTON_MOUSE_DOWN;
                // check if current button selected is not a nullptr and this.m Selected is false
                if (currentSelected != nullptr && mSelected == false)
                {
                    currentSelected->setSelected(false);
                }
                // Set this.mSelected to true
                mSelected = true;
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentState = LButtonState::BUTTON_MOUSE_UP;
                break;

            }
        }
    }
}

bool LButton::isSelected()
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
    SDL_Color MouseOutColour = { 255, 255, 255, SDL_ALPHA_OPAQUE };
    SDL_Color MouseOverMotionColour = { 255, 0, 0, SDL_ALPHA_OPAQUE };
    SDL_Color MouseDownColour = { 0, 255, 0, SDL_ALPHA_OPAQUE };
    SDL_Color MouseUpColour = { 255, 0, 0, SDL_ALPHA_OPAQUE };
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

std::string LButton::getNumber()
{
    return mNumber;
}

void LButton::setNumber(std::string& inputNumber)
{
    mNumber = inputNumber;
}
