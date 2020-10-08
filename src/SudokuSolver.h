/* Sudoku solver class */
#pragma once
#include <iostream>

namespace Sudoku 
{
	// Struct for ignoring a number specified at row and col (for the Sudoku generating class)
	struct Ignore
	{
		int num = 0;
		int row = 0;
		int col = 0;
	};

	// Sudoku solver class
	class Solver
	{
	private:
		// Pointer to the Sudoku 1D grid and must be of size 9 x 9 = 81
		int* mGrid;

		// Set number to ignore and a modifier (for the Sudoku generator class)
		bool mGenModifier;
		Ignore mNumToIgnore;

	private:
		// Set and get element of 1D array using row and col
		inline void setElement(const int row, const int col, const int num);
		inline int getElement(const int row, const int col) const;

		// Check if element is valid for its row, col, and the block of 3 x 3 its in
		bool checkValid(const int inputRow, const int inputCol, const int num) const;

	public:
		// Constructor
		Solver();

		// Set generator modifier (for the Sudoku generator class)
		void setGenModifier(const bool input);

		// Set Sudoku array (Ignore input paramaters is for the Sudoku generator class)
		void setGrid(int* grid, const Ignore& ignoreInput = { 0, 0, 0 });

		// Solve Sudoku with backtracking
		bool solve();

		// Display Sudoku to console (for debugging)
		void display() const;

	};

};