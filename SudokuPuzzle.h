#pragma once
#include "Cell.h"
#include "CellGroup.h"
#include <iostream>
#include <fstream>
#include <chrono>

class SudokuPuzzle {
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void solve(const char filenameIn[]);

private:
	void output() const;
	void readPuzzle(const char filenameIn[]);

	CellGroup m_blocks[9];
	CellGroup m_rows[9];
	CellGroup m_columns[9];
	
	int solvedCounter = 0;
};