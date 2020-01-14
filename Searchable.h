//
// Created by giladasher on 13/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SEARCHABLE_H
#define SEARCHPROBLEMSOLVER_SEARCHABLE_H

#include "State.h"
#include <vector>

using namespace std;

template<class Problem>
class Searchable {

public:
	virtual State<Problem> getInitialState() = 0;

	virtual bool isGoalState(State<Problem>) = 0;

	virtual vector<State<Problem>> getAllPossibleStates() = 0;

};

#endif //SEARCHPROBLEMSOLVER_SEARCHABLE_H
