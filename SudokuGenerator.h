/* Sudoku generator class */
#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "SudokuSolver.h"

namespace Sudoku
{
	class Generator
	{
	private:
		// Sudoku 1D array and must be of size 9 x 9 = 81
		int* mGrid;

		// Sudoku solution 1D array and must be of size 9 x 9 = 81
		int* mGridSolution;

	private:
		// Set and get element of 1D array using row and col
		inline void setElement(const int row, const int col, const int num);
		inline int getElement(const int row, const int col) const;

		// Swapping
		void swapNumbers(const int index1, const int index2);
		void swapRows(const int row1, const int row2);
		void swapCols(const int col1, const int col2);
		void swapRowBlocks(const int rowBlock1, const int rowBlock2);
		void swapColBlocks(const int colBlock1, const int colBlock2);

		// Fill next row with previous row with n shifts
		void fillNextRow(const int previousRow, const int nextRow, const int shifts);

		// Copy this grid into grid
		void copyGrid(int* grid) const;

		// Create a random completed Sudoku array using shuffling
		void createCompletedSudoku();

	public:
		// Constructor for intialisation
		Generator();

		// Generate Sudoku from completed Sudoku and return a pointer to it
		void generate(int* grid, int* solutionGrid);

		// Display Sudoku to console (for debugging)
		void display() const;

	};

};