#include "SudokuSolver.h"

SudokuSolver::SudokuSolver()
	: mSudokuArray(nullptr), mSolutions(0), mFirstSolutionOnly(true),
	mIsUnique(Unique::Yes), mGenModifier(false), mNumToIgnore({ 0, 0, 0 })
{

}

SudokuSolver::~SudokuSolver()
{
	deleteAllSolutions();
}

//--------------------------------------Private methods----------------------------------------//
inline void SudokuSolver::setElement(const int row, const int col, const int num)
{
	mSudokuArray[row * 9 + col] = num;
}

bool SudokuSolver::checkValid(const int inputRow, const int inputCol, const int num)
{
	// if number is valid i.e. not found in row, col, or block then return true

	// check row
	for (int col = 0; col < 9; col++)
	{
		if (getElement(inputRow, col) == num)
		{
			return false;
		}
	}

	// check col
	for (int row = 0; row < 9; row++)
	{
		if (getElement(row, inputCol) == num)
		{
			return false;
		}
	}

	// check block
	const int startRow = (int)(inputRow / 3) * 3;
	const int startCol = (int)(inputCol / 3) * 3;

	const int endRow = startRow + 3;
	const int endCol = startCol + 3;

	for (int row = startRow; row < endRow; row++)
	{
		for (int col = startCol; col < endCol; col++)
		{
			if (getElement(row, col) == num)
			{
				return false;
			}
		}
	}

	// number not found in row, col, nor block so return true;
	return true;
}

void SudokuSolver::clearSudoku()
{
	mSolutions = 0;
	mIsUnique = Unique::Yes;
	for (int i = 0; i < 81; i++)
	{
		mSudokuArray[i] = 0;
	}
	deleteAllSolutions();
}

void SudokuSolver::addArray()
{
	int* solutionArray = new int[81];
	// delete[] solutionArray
	for (int i = 0; i < 81; i++)
	{
		solutionArray[i] = mSudokuArray[i];
	}

	mAllSolutions.push_back(solutionArray);
}

void SudokuSolver::deleteAllSolutions()
{
	// Delete all solutions
	for (const int* solution : mAllSolutions)
	{
		delete[] solution;
	}

	// Empty vector of int pointers
	mAllSolutions.clear();
}

//--------------------------------------Public methods----------------------------------------//
void SudokuSolver::setSudoku(int* inputArray)
{
	mSolutions = 0;
	// Assume there is a unique solution
	mIsUnique = Unique::Yes;
	mSudokuArray = inputArray;
	deleteAllSolutions();
}

void SudokuSolver::setGenModifier(const bool input)
{
	mGenModifier = input;
}

void SudokuSolver::setSudoku(int* inputArray, const Ignore& input)
{
	// Ignore the choosing input number when that number is selected at the row and col
	mNumToIgnore = input;
	mSolutions = 0;
	// Assume there is a unique solution
	mIsUnique = Unique::Yes;
	mSudokuArray = inputArray;
}

void SudokuSolver::setFirstSolutionOnly(const bool input)
{
	mFirstSolutionOnly = input;
}

Unique SudokuSolver::isUniqueSolution() const
{
	return mIsUnique;
}

inline int SudokuSolver::getElement(const int row, const int col)
{
	return mSudokuArray[row * 9 + col];
}

bool SudokuSolver::solveSudoku()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (getElement(row, col) == 0)
			{
				for (int num = 1; num < 10; num++)
				{
					// If generator modifier is set to true and the row, col and number match then skip to next iteration
					if (!(mGenModifier && mNumToIgnore.row == row && mNumToIgnore.col == col && mNumToIgnore.num == num))
					{
						// if number is valid i.e. not found in row, col, or block then return true
						if (checkValid(row, col, num))
						{
							setElement(row, col, num);

							if (solveSudoku())
							{
								return true;
							}
							// set element to 0 since num did not work for further recursion call(s)
							setElement(row, col, 0);
						}
					}
				}
				// back track to previous element
				return false;
			}
		}
	}
	// Increment number of solutions
	mSolutions++;

	// Add solution to vector of solutions
	addArray();

	// No unique solution found if number of solutions is greater than 1
	if (mSolutions > 1)
	{
		mIsUnique = Unique::No;
	}

	// If only the first solution should be found
	if (mFirstSolutionOnly)
	{
		// Solver complete
		mIsUnique = Unique::Unknown;
		return true;
	}
	// Else find all solutions
	else
	{
		// Solver not complete until all solutions found
		return false;
	}
}

void SudokuSolver::displaySudoku()
{
	for (const int* solution : mAllSolutions)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				std::cout << solution[row * 9 + col] << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << "----------------------------\n";
	}

}
