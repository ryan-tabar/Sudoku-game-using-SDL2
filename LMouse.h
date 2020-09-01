#pragma once
#include <SDL.h> 
#include <iostream>
#include "LTexture.h"

enum class LButtonState
{
    BUTTON_MOUSE_OUT = 0,
    BUTTON_MOUSE_OVER_MOTION = 1,
    BUTTON_MOUSE_DOWN = 2,
    BUTTON_MOUSE_UP = 3,
};

// A mouse button class
class LButton : public LTexture
{
private:
    // Currently used state
    LButtonState mCurrentState;

    // Selected variable
    bool mSelected;

    // Button dimesnions and top left position
    SDL_Rect mButtonRect;

    // Number to be displayed
    std::string mNumber;

    // Default mouse colours if not editable
    SDL_Color MouseOutColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
    SDL_Color MouseOverMotionColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
    SDL_Color MouseDownColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple
    SDL_Color MouseUpColour = { 159, 101, 152, SDL_ALPHA_OPAQUE }; // purple

    // Uneditable button
    bool mEditable;

public:
    // Initialises internal variables
    LButton();

    // Set SDL_Rect
    void setButtonRect(const SDL_Rect& const inputRect);

    // Get SDL_Rect
    SDL_Rect getButtonRect() const;

    // Set Editability
    void setEditable(const bool input);

    // Get Editability
    bool getEditable();

    // Handles mouse event
    void handleEvent(const SDL_Event* const E, LButton*& currentSelected);

    // Get selected variable
    bool isSelected() const;

    // Set selected variable
    void setSelected(bool input);

    // Shows button colour
    void renderButton();

    // Get number
    std::string getNumber() const;

    // Set number
    void setNumber(const std::string& const inputNumber);
    
};