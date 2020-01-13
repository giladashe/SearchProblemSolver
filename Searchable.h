//
// Created by giladasher on 13/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SEARCHABLE_H
#define SEARCHPROBLEMSOLVER_SEARCHABLE_H

#include "State.h"
#include <vector>

using namespace std;

template<class T>
class Searchable {
	virtual State<T> getInitialState() = 0;

	virtual bool isGoalState(State<T>) = 0;

	virtual vector<State<T>> getAllPossibleStates() = 0;

};

#endif //SEARCHPROBLEMSOLVER_SEARCHABLE_H
