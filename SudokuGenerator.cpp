#include "SudokuGenerator.h"

SudokuGenerator::SudokuGenerator()
	: mSudokuArray(nullptr), mSudokuSolution(nullptr)
{

}

//--------------------------------------Private methods----------------------------------------//
inline void SudokuGenerator::setElement(const int row, const int col, const int num)
{
	mSudokuArray[row * 9 + col] = num;
}

inline int SudokuGenerator::getElement(const int row, const int col) const
{
	return mSudokuArray[row * 9 + col];
}

void SudokuGenerator::swapNumbers(const int index1, const int index2)
{
	// Only works if they're not from the same index
	mSudokuArray[index1] = mSudokuArray[index1] ^ mSudokuArray[index2];
	mSudokuArray[index2] = mSudokuArray[index1] ^ mSudokuArray[index2];
	mSudokuArray[index1] = mSudokuArray[index1] ^ mSudokuArray[index2];
}

void SudokuGenerator::swapRows(const int row1, const int row2)
{
	for (int col = 0; col < 9; col++)
	{
		swapNumbers(row1 * 9 + col, row2 * 9 + col);
	}
}

void SudokuGenerator::swapCols(const int col1, const int col2)
{
	for (int row = 0; row < 9; row++)
	{
		swapNumbers(row * 9 + col1, row * 9 + col2);
	}
}

void SudokuGenerator::swapRowBlocks(const int rowBlock1, const int rowBlock2)
{
	int startRow1 = rowBlock1 * 3;
	int startRow2 = rowBlock2 * 3;

	for (int i = 0; i < 3; i++)
	{
		swapRows(startRow1 + i, startRow2 + i);
	}
}

void SudokuGenerator::swapColBlocks(const int colBlock1, const int colBlock2)
{
	int startCol1 = colBlock1 * 3;
	int startCol2 = colBlock2 * 3;

	for (int i = 0; i < 3; i++)
	{
		swapCols(startCol1 + i, startCol2 + i);
	}
}

void SudokuGenerator::fillNextRow(const int previousRow, const int nextRow, const int shifts)
{
	for (int col = 0; col < (9 - shifts); col++)
	{
		setElement(nextRow, col, getElement(previousRow, col + shifts));
	}

	for (int col = (9 - shifts); col < 9; col++)
	{
		setElement(nextRow, col, getElement(previousRow, col - 9 + shifts));
	}
}

void SudokuGenerator::copyArray(int* copyArray) const
{
	for (int i = 0; i < 81; i++)
	{
		copyArray[i] = mSudokuArray[i];
	}
}

void SudokuGenerator::createCompletedSudoku()
{
	// Set random seed using time
	srand((unsigned int)time(NULL));

	// 1. Fill first row with numbers 1 to 9
	for (int i = 0; i < 9; i++)
	{
		mSudokuArray[i] = i + 1;
	}

	// 2. Shuffle first row of 9 numbers
	int swaps = 50;
	for (int i = 0; i < swaps; i++)
	{
		int randIndex1 = rand() % 9;
		int randIndex2 = rand() % 9;
		if (randIndex1 != randIndex2)
		{
			swapNumbers(randIndex1, randIndex2);
		}
	}

	// 3. Fill second and third row by previous row but shifted by 3
	fillNextRow(0, 1, 3);
	fillNextRow(1, 2, 3);

	// 4. Fill fourth row by previous row but shifted by 1
	fillNextRow(2, 3, 1);

	// 5. Fill fith and sixth row by previous row but shifted by 3
	fillNextRow(3, 4, 3);
	fillNextRow(4, 5, 3);

	// 6. Fill seventh row by previous row but shifted by 1
	fillNextRow(5, 6, 1);

	// 7. Fill eith and ninth row by previous row but shifted by 3
	fillNextRow(6, 7, 3);
	fillNextRow(7, 8, 3);

	// 8. Shuffle rows within every row block
	int shuffles = 10;
	for (int rowBlock = 0; rowBlock < 3; rowBlock++)
	{
		for (int shuffle = 0; shuffle < shuffles; shuffle++)
		{
			int randRow1 = rowBlock * 3 + (rand() % 3);
			int randRow2 = rowBlock * 3 + (rand() % 3);
			if (randRow1 != randRow2)
			{
				swapRows(randRow1, randRow2);
			}
		}
	}

	// 9. Shuffle cols within every col block
	for (int colBlock = 0; colBlock < 3; colBlock++)
	{
		for (int shuffle = 0; shuffle < shuffles; shuffle++)
		{
			int randCol1 = colBlock * 3 + (rand() % 3);
			int randCol2 = colBlock * 3 + (rand() % 3);
			if (randCol1 != randCol2)
			{
				swapCols(randCol1, randCol2);
			}
		}
	}

	// 10. Shuffle row blocks
	for (int shuffle = 0; shuffle < shuffles; shuffle++)
	{
		int randRowBlock1 = rand() % 3;
		int randRowBlock2 = rand() % 3;
		if (randRowBlock1 != randRowBlock2)
		{
			swapRowBlocks(randRowBlock1, randRowBlock2);
		}
	}

	// 11. Shuffle col blocks
	for (int shuffle = 0; shuffle < shuffles; shuffle++)
	{
		int randColBlock1 = rand() % 3;
		int randColBlock2 = rand() % 3;
		if (randColBlock1 != randColBlock2)
		{
			swapColBlocks(randColBlock1, randColBlock2);
		}
	}

	// 12. Store solution in solution array
	copyArray(mSudokuSolution);

}

//--------------------------------------Public methods----------------------------------------//
void SudokuGenerator::generateSudoku(int* inputArray, int* solutionArray)
{
	// Set the Sudoku array and solution array
	mSudokuArray = inputArray;
	mSudokuSolution = solutionArray;

	// Create completed Sudoku
	createCompletedSudoku();

	// Set random seed using time
	srand((unsigned int)time(NULL));

	// Create Sudoku solver object
	SudokuSolver SS;

	// Set the Sudoku solver to have the generator modifier
	SS.setGenModifier(true);

	// Create array of bool types to track if elements have been removed from the main array
	bool removed[81] = { };

	// Create a temporary duplicate array
	int duplicateArray[81];

	// Current number to be determined to be removed
	int removingNumber = 0;

	// Elements to remove
	int toRemove = 50;

	while (toRemove)
	{
		// 1. Pick a random number you haven't tried removing before
		int randRow = rand() % 9;
		int randCol = rand() % 9;
		if (!removed[randRow * 9 + randCol])
		{
			// 2. Remove the number, then run solver without the number to be determined to be removed
			removingNumber = getElement(randRow, randCol);
			copyArray(duplicateArray);
			duplicateArray[randRow * 9 + randCol] = 0;
			Ignore numToIgnore = { removingNumber, randRow, randCol };
			SS.setSudoku(duplicateArray, numToIgnore);

			// 3. If the solver does not find a solution, then remove number
			if (!SS.solveSudoku())
			{
				setElement(randRow, randCol, 0);
				removed[randRow * 9 + randCol] = true;
				toRemove--;
			}
		}
		// 4. Repeat, until enough numbers removed
	}

}

void SudokuGenerator::displaySudoku() const
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			std::cout << getElement(row, col) << ", ";
		}
		std::cout << std::endl;
	}
}
