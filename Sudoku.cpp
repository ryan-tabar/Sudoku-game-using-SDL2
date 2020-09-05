#include "Sudoku.h"

//----------------------------------Constructor and Destructor---------------------------------//
Sudoku::Game::Game()
	: mWindowHeight(900), mWindowWidth(810),
	  mGridHeight(810), mGridWidth(810),
	  mGridRows(9), mGridCols(9),
	  mTotalCells(81),
	  mWindow(nullptr), mRenderer(nullptr), mFont(nullptr), mFontSize(mGridHeight/9),
	  mClearColour({ 0, 0, 0, SDL_ALPHA_OPAQUE })
{

}

Sudoku::Game::~Game()
{
	freeTextures();
	close();
}

//--------------------------------------Private methods----------------------------------------//
bool Sudoku::Game::initialiseSDL()
{
	// Set success initialisation flag
	bool success = true;

	// Initalise SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL could not intialise! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Initialise SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialise! Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	// Create window
	mWindow = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, SDL_WINDOW_SHOWN);
	if (mWindow == nullptr)
	{
		std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Create renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	if (mRenderer == nullptr)
	{
		std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	// Load font for text
	mFont = TTF_OpenFont("Resources/VALENTIN.TTF", mFontSize);
	if (mFont == nullptr)
	{
		std::cout << "Failed to load lazy font! Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	return success;
}

inline int Sudoku::Game::getIndex(int row, int col) const
{
	return row * mGridRows + col;
}

void Sudoku::Game::generateSudoku()
{
	int SudokuGrid[81] = { };
	int solution[81] = { };
	Generator G;
	G.generate(SudokuGrid, solution);
	for (int i = 0; i < 81; i++)
	{
		// Set number and solution
		mGrid[i].setNumber(SudokuGrid[i]);
		mGrid[i].setSolution(solution[i]); 
	}
}

void Sudoku::Game::setCells()
{
	// Define Button dimensions
	const int buttonWidth = mGridWidth / mGridCols;
	const int buttonHeight = mGridHeight / mGridRows;

	// Create offsets for grid display
	const float borderFactor = 0.01;
	const float thinBorderFactor = 0.5;
	const float buttonStartOffSetFactor = 0.33;
	int buttonStartWidthOffSet;
	int buttonStartHeightOffSet;
	int buttonWidthOffSet;
	int buttonHeightOffSet;
	const int textureWidthOffSet = mFontSize / 5;
	const int textureHeightOffSet = mFontSize / 10;

	// Initialise button size and placement on the Sudoku grid.
	for (int row = 0; row < mGridRows; row++)
	{
		for (int col = 0; col < mGridCols; col++)
		{
			// Get index and bind renderer
			int index = getIndex(row, col);

			// Set button width offsets base on thickness of borders
			if ((col + 1) % 3 == 0 && (col + 1) != mGridCols) buttonWidthOffSet = borderFactor * mGridWidth;
			else buttonWidthOffSet = borderFactor * mGridWidth * thinBorderFactor;

			// Set button height offsets based on thickness of borders
			if ((row + 1) % 3 == 0 && (row + 1) != mGridRows) buttonHeightOffSet = borderFactor * mGridHeight;
			else buttonHeightOffSet = borderFactor * mGridHeight * thinBorderFactor;

			// Set button start positon offsets
			buttonStartWidthOffSet = buttonWidthOffSet * buttonStartOffSetFactor;
			buttonStartHeightOffSet = buttonWidthOffSet * buttonStartOffSetFactor;

			// Set button and texture positions and dimensions
			mGrid[index].setButtonRect({ col * buttonWidth + buttonStartWidthOffSet, row * buttonHeight + buttonStartHeightOffSet, buttonWidth - buttonWidthOffSet, buttonHeight - buttonHeightOffSet });
			mGrid[index].setTextureRect({ col * buttonWidth + textureWidthOffSet, row * buttonHeight + textureHeightOffSet, NULL, NULL });

			// Get character
			char charNumber = mGrid[index].getNumber();

			// load texture
			mGrid[index].loadFontTexture(mRenderer, mFont, charNumber);
		}
	}


}

void Sudoku::Game::freeTextures()
{
	for (int cell = 0; cell < mTotalCells; cell++)
	{
		mGrid[cell].freeTexture();
	}
}

//--------------------------------------Public methods----------------------------------------//
void Sudoku::Game::play()
{
	// Initialise SDL
	if (!initialiseSDL())
	{
		close();
	}

	// Generate Sudoku and set numbers
	generateSudoku();

	// Set buttons, textures, and font for the cells
	setCells();

	// Enable text input
	SDL_StartTextInput();

	// Set first current button selected
	Cell* currentCellSelected = &mGrid[0];
	for (int cell = 0; cell < mTotalCells; cell++)
	{
		if (mGrid[cell].isEditable())
		{
			currentCellSelected = &mGrid[cell];
			currentCellSelected->setSelected(true);
			break;
		}
	}

	// Loop variables
	SDL_Event event;
	bool stop = false;
	bool completed = false;

	while (!stop)
	{
		// Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			// Handle quiting and completion
			if (event.type == SDL_QUIT || completed)
			{
				stop = true;
			}
			// Handle button events for mouse
			for (int cell = 0; cell < mTotalCells; cell++)
			{
				// If editable
				if (mGrid[cell].isEditable())
				{
					// Change the current cell selected if a different button has been selected
					mGrid[cell].handleMouseEvent(&event, (Button*&)currentCellSelected);
				}
			}
			// Handle keyboard events for current cell
			currentCellSelected->handleKeyboardEvent(&event, mRenderer, mFont);
		}

		// Check if complete
		for (int cell = 0; cell < mTotalCells; cell++)
		{
			if (!mGrid[cell].isCorrect())
			{
				completed = false;
				break;
			}
			completed = true;
		}

		// Clear screen to black
		SDL_SetRenderDrawColor(mRenderer, mClearColour.r, mClearColour.g, mClearColour.b, mClearColour.a);
		SDL_RenderClear(mRenderer);

		// Render buttons and texture of each cell to backbuffer
		for (int cell = 0; cell < mTotalCells; cell++)
		{
			mGrid[cell].renderButton(mRenderer);
			mGrid[cell].renderTexture(mRenderer);
		}

		// Update screen from backbuffer and clear backbuffer
		SDL_RenderPresent(mRenderer);

		// Slow down program becuase it doesn't need to run very fast
		SDL_Delay(10);
	}

	// Disable text input
	SDL_StopTextInput();

	// Display whether they completed successfully or closed before completing
	if (completed)
	{
		std::cout << "Congratulations! You successfully completed the Sudoku puzzle!" << std::endl;
	}
	else
	{
		std::cout << "Oh no! You closed before completing the Sudoku puzzle!" << std::endl;
	}

	// Free button textures
	freeTextures();

	// Destroy and quit
	close();
}

void Sudoku::Game::close()
{
	// Destroy
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mRenderer = nullptr;
	mWindow = nullptr;

	// Free font
	TTF_CloseFont(mFont);
	mFont = nullptr;

	// Quit
	SDL_Quit();
	TTF_Quit();
}
