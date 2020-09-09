# Sudoku game in C++ using SDL2
![ScreenshotOfProgram](Resources/ScreenshotOfProgram.png?raw=true)

## Requirements
- Microsoft Visual Studio
- SDL2 (already included in Dependencies folder)

## How to build and run
- Open Microsoft Visual Studio
- Click "Clone a repository"
- Copy and paste respository link
- Hit F5 to build and run (in either Debug or Release)
- If you want to run from the generated executable, make sure the dll and resource folder are in the same directory as the executable.

## Framework diagram
Key: 
  - Arrow = inheritance
  - Line = composition

![Framework](Resources/SudokuFramework.png?raw=true)

- All 81 (9 x 9) cells and the stopwatch act as buttons 
- The stopwatch and any cell set to a non-zero value during the generation of the puzzle act as buttons that cannot be clicked
- "New" button generates a new Sudoku
- "Check" checks if attempt is correct

## Possible things to add
- Add difficulty setting by changing the number of cells removed in the generator class
- When a cell is selected, highlight the block of 9, row of 9, and column of 9 and show which numbers cannot be placed in that cell
