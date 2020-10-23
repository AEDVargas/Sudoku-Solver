#include "CellGroup.h"

CellGroup::CellGroup(void)
{
	//Create new cell objects
    for (int i = 0; i < 9; ++i) {
        m_cells[i] = new Cell();
    }
}

CellGroup::~CellGroup(void)
{
	//Delete the cell objects upon exiting the program
	for (int i = 0; i < 9; ++i) {
		if (!m_cells) {
			delete m_cells[i];
			m_cells[i] = nullptr;
		}
	}
}
