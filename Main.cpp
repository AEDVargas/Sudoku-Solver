#include "SudokuPuzzle.h"
#include <iostream>

using namespace std;

int main(int const argc, char **) {
	
	SudokuPuzzle puzzle;

	puzzle.solve("sudoku_puzzle.txt");

	system("PAUSE");
	return 0;
}