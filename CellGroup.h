#pragma once
#include "Cell.h"

class CellGroup
{
public:
	CellGroup(void);
	~CellGroup(void);

	//Set the appropriate values in the cell
	void setCell(int const index, Cell* const cell) { m_cells[index] = cell; }

	//Get the values of the cell
	Cell* getCell(int index) const { return m_cells[index]; }

private:
	//Array of pointer
	Cell* m_cells[9];
};
