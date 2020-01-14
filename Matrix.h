//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_MATRIX_H
#define SEARCHPROBLEMSOLVER_MATRIX_H

#include "Searchable.h"

template<class Problem>
class Matrix : public Searchable<Problem> {
	vector<vector<State<Problem>>> _states;
	State<Problem> _initialState;
	vector<State<Problem>> _goalStates;
	int _rows;
	int _columns;

	bool inRange(int i, int j) {
		return i >= 0 && i < _rows && j >= 0 && j < _columns;
	}

public:

	Matrix(string matrixStr) {
		//todo make matrix from str
	}

	State<Problem> getInitialState() override {
		return this->_initialState;
	}

	bool isGoalState(State<Problem> state) override {
		bool isGoal = false;
		for (auto &currentState:_goalStates) {
			//todo override ==
			if (currentState == state) {
				isGoal = true;
			}
		}
		return isGoal;
	}

	vector<State<Problem>> getAllPossibleStates() override {
		//todo this function using "in range"
		return vector<State<Problem>>();
	}
};

#endif //SEARCHPROBLEMSOLVER_MATRIX_H
