/* Sudoku solver class */
#pragma once
#include <iostream>
#include <vector>

// Enumeration for defining Sudoku solution(s)
enum class Unique
{
	No = 0,
	Yes = 1,
	Unknown = 2,
};

// Struct for ignoring a number at certain coordinates (for generating Sudoku class)
struct Ignore
{
	int num = 0;
	int row = 0;
	int col = 0;
};

// Sudoku solver class
class SudokuSolver
{
private:
	// Pointer to the Sudoku 1D array
	int* mSudokuArray;

	// Set element of 1D array using row and col
	inline void setElement(const int row, const int col, const int num);

	// Check if element is valid for its row, col, and the block of 3 x 3 its in
	bool checkValid(const int inputRow, const int inputCol, const int num);

	// Clear Sudoku array
	void clearSudoku();

	// Track number of solutions
	int mSolutions;

	// Find first solution only
	bool mFirstSolutionOnly;

	// Check if there is a unique solution
	Unique mIsUnique;

	// A modifier flag (for the generating Sudoku class)
	bool mGenModifier;

	// Number, row and col to ignore (for the generating Sudoku class)
	Ignore mNumToIgnore;

	// Vector of pointers to the solutions
	std::vector<int*> mAllSolutions;

	// Add current Sudoku array to all solutions 
	void addArray();

	// Delete all solutions
	void deleteAllSolutions();

public:
	// Constructor
	SudokuSolver();

	// Destructor
	~SudokuSolver();

	// Set Sudoku array, reset number of solutions, and assume unique solution is true
	void setSudoku(int* inputArray);

	// Set generator modifier (for the generator class)
	void setGenModifier(const bool input);

	// Set Sudoku array overide function (for the generator class)
	void setSudoku(int* inputArray, const Ignore& input);

	// Set find first solution only flag
	void setFirstSolutionOnly(const bool input);

	// Return if unique solution
	Unique isUniqueSolution() const;

	// Get element from 1D array using row and col
	inline int getElement(const int row, const int col);

	// Solve Sudoku with backtracking
	bool solveSudoku();

	// Display Sudoku to console 
	void displaySudoku();

};