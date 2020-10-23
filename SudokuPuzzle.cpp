#include "SudokuPuzzle.h"
#include <Windows.h>

using namespace std;

SudokuPuzzle::SudokuPuzzle(void) {
}

SudokuPuzzle::~SudokuPuzzle(void) {
}

void SudokuPuzzle::solve(const char filenameIn[]) {
	// Read puzzle from text file
	readPuzzle(filenameIn);

	// Get start time
	const auto startTime = chrono::high_resolution_clock::now();

	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	//Counters
	bool completion = false;
	int candidateCounter = 0;
	int iterationCounter = 0;
	int previousSize = 0;
	int cellSolved = 0;

	do
	{
		for (int row = 0; row < 9; ++row) {
			for (int column = 0; column < 9; ++column) {
				for (int i = 0; i < 9; ++i) { //Removes candidate values to the final value
					if (m_rows[row].getCell(i)->getValue() != 0) {
						m_rows[row].getCell(column)->deleteCandidate(m_rows[row].getCell(i)->getValue());
					}
					if (m_columns[row].getCell(i)->getValue() != 0) {
						m_columns[row].getCell(column)->deleteCandidate(m_columns[row].getCell(i)->getValue());
					}
					if (m_blocks[row].getCell(i)->getValue() != 0) {
						m_blocks[row].getCell(column)->deleteCandidate(m_blocks[row].getCell(i)->getValue());
					}
					if (m_rows[row].getCell(i)->candidateListSize() == 1 && m_rows[row].getCell(i)->getGiven() == false) {
						m_rows[row].getCell(i)->setValue(m_rows[row].getCell(i)->getCList(0));
						m_rows[row].getCell(i)->setGiven(true);
						++solvedCounter;
						++cellSolved;
					}
				}
				candidateCounter += m_rows[row].getCell(column)->candidateListSize(); //Adds the candidate values to counter
			}
		}
		//Checks if the puzzle is complete or hasn't changed any values since the last iteration
		if (solvedCounter == 81) {
			completion = true;
		}
		else if (previousSize == solvedCounter) {
			//||Hidden Singles method||
			completion = true;
		}
		else {
			//Set previous size of solved amount of cells and increment iteration counter
			previousSize = solvedCounter;
			++iterationCounter;
		}
	} while (completion == false); //If solved counter reaches 81 or has same value as previous iteration then stop loop

	 //Get end time
	const auto endTime = chrono::high_resolution_clock::now();
	const auto duration = (endTime - startTime).count();

	//Output results and tests
	QueryPerformanceCounter(&end);
	const double durationInSeconds = (end.QuadPart - start.QuadPart) / (static_cast<double> (frequency.QuadPart));

	//Printing stats
	cout << "Completed in nanoseconds      : " << duration << endl;
	cout << "Completed in seconds          : " << durationInSeconds << endl;
	cout << "Total candidates considered   : " << candidateCounter << endl;
	cout << "Total iterations through grid : " << iterationCounter << endl;
	cout << "Total solved cells            : " << solvedCounter << endl ;
	cout << "Cells solved (not given)      : " << cellSolved << endl << endl;
	 
	// Output the solved puzzle
	output();
}

void SudokuPuzzle::readPuzzle(const char filenameIn[]) {

	fstream input = fstream(filenameIn); //Input data from file

	int tempValue;
	int given = false;

	int indexOne = 0;
	int indexTwo = 0;
	int index = 0;
	int r_index = 0;
	int c_index = 0;
	int value = 0;

	//Nested loops to get values for rows, columns and grids
	for (int row = 0; row < 9; ++row) {
		for (int column = 0; column < 9; ++column) {
			input >> tempValue; //Input value from file

			//If value is given from file set bool true and increment solved counter - else false
			if (tempValue != 0) {
				given = true;
				++solvedCounter;
			}
			else {
				given = false;
			}
			//Populate groups reading from rows or columns
			m_rows[row].setCell(column, new Cell(tempValue, given));
			m_columns[column].setCell(row, m_rows[row].getCell(column));

			//Gets the sizes of the block
			const int r_block = row / 3;
			const int c_block = column / 3;

			//Checks size of the row part of the block and sets the appropiate indexes to populate block
			switch (r_block)
			{
			case 0:
				r_index = row;
				index = c_block;
				break;
			case 1:
				r_index = row - 3;
				index = 3 + c_block;
				break;
			default:
				r_index = row - 6;
				index = 6 + c_block;
				break;
			}

			//Checks size of the column part of the block and sets the appropiate indexes to populate block
			switch (c_block)
			{
			case 0:
				c_index = column;
				break;
			case 1:
				c_index = column - 3;
				break;
			default:
				c_index = column - 6;
				break;
			}

			//Sets value for the index of the cell
			value = c_index + (r_index * 3);
			//Assigns index values
			indexOne = index;
			indexTwo = value;
			//Set value for block cell group
			m_blocks[indexOne].setCell(indexTwo, m_rows[row].getCell(column));
		}
	}

}

void SudokuPuzzle::output() const {
	//Outputs the final puzzle
	ofstream output("sudoku_solution.txt");
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			output << m_rows[i].getCell(j)->getValue() << " "; //Stream out to file
			cout << m_rows[i].getCell(j)->getValue() << " "; //Stream out to console
		}
		output << endl;
		cout << endl;
	}
	cout << endl;
}
