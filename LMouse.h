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
    BUTTON_TOTAL = 4
};

// The mouse button
class LButton : public LTexture
{
private:
    // Currently used global sprite
    LButtonState mCurrentState;

    // Selected variable
    bool mSelected;

    // Button dimesnions and top left position
    SDL_Rect mButtonRect;

    // Number to be displayed
    std::string mNumber;

public:
    // Initialises internal variables
    LButton(SDL_Renderer* inputRenderer = nullptr);

    // Set SDL_Rect
    void setButtonRect(SDL_Rect& inputRect);

    // Get SDL_Rect
    SDL_Rect getButtonRect();

    // Handles mouse event
    void handleEvent(SDL_Event* E, LButton* currentSelected);

    // Get selected variable
    bool isSelected();

    // Set selected variable
    void setSelected(bool input);

    // Shows button colour
    void renderButton();

    // Get number
    std::string getNumber();

    // Set number
    void setNumber(std::string& inputNumber);
    
};