/* Sudoku generator class */
#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "SudokuSolver.h"

// A struct to track removed elements
struct RemovedElements
{
	bool removed = false;
};

// Sudoku generator class
class SudokuGenerator
{
private:
	// Sudoku 1D array of size 9 x 9 = 81
	int* mSudokuArray;

	// Clear array with 0's
	void clearSudoku();

	// Set element of 1D array using row and col
	inline void setElement(const int row, const int col, const int num);

	// Swap 2 values at 2 index's
	void swapNumbers(const int index1, const int index2);

	// Fill next row with previous row but shifted by n shifts
	void fillNextRow(const int previousRow, const int nextRow, const int shifts);

	// Swap rows
	void swapRows(const int row1, const int row2);

	// Swap cols
	void swapCols(const int col1, const int col2);

	// Swap row blocks
	void swapRowBlocks(const int rowBlock1, const int rowBlock2);

	// Swap col blocks
	void swapColBlocks(const int colBlock1, const int colBlock2);

	// Create a random completed Sudoku array using shuffling
	void createCompletedSudoku();

	// Copy Sudoku array into argument
	void copyArray(int* copyArray);

public:
	// Construct empty array
	SudokuGenerator();

	// Set array to be generated on
	void setSudoku(int* inputArray);

	// Get element from 1D array using row and col
	inline int getElement(const int row, const int col);

	// Generate Sudoku from completed Sudoku and return a pointer to it
	void generateSudoku();

	// Display Sudoku to console
	void displaySudoku();

};