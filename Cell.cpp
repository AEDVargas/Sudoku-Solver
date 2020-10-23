#include "Cell.h"

Cell::~Cell(void)
{
}

void Cell::populateCList() {
	//Populate temporary values for the candidate list
    for (int i = 1; i <= 9; ++i) {
        m_candidateList.push_back(i);
    }
}

void Cell::deleteCandidate(int const _candidate) {
	//Delete candidate from list given from parameter
    for (int i = 0; i < m_candidateList.size(); ++i) {
        if (_candidate == m_candidateList[i]) {
            m_candidateList.erase(m_candidateList.begin() + i);
            break;
        }
    }

}