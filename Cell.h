#pragma once
#include <iostream> 
#include <vector>

using namespace std;

class Cell {
public:
	Cell(int const value, bool const given) :
		m_value(value), m_given(given) {
		populateCList();
	}
	Cell(void) :
		m_value(0), m_given(false) {
		populateCList();
	}
	~Cell(void);

	//Getter/Accesssor
	int getValue() const { return m_value; } 
	bool getGiven() const { return m_given; } 
	int candidateListSize() const { return m_candidateList.size(); } 
	int getCList(int const index) const { return m_candidateList[index]; }

	//Setter/Mutator
	void setValue(int const value) { m_value = value; }
	void setGiven(bool const given) { m_given = given; }

	//Delete a value from the candidate list
	void deleteCandidate(int const d_Candidate); 

	//Set temporary value for candidate list
	void populateCList();

private:
	vector<int> m_candidateList;
	int m_value;
	bool m_given;
};