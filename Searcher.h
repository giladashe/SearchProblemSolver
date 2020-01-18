//
// Created by giladasher on 13/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SEARCHER_H
#define SEARCHPROBLEMSOLVER_SEARCHER_H

#include "Searchable.h"

template<class Problem, class Solution>
class Searcher {
	int _numOfNodes = 0;
public:
	virtual Solution search(Searchable<Problem> *searchable) = 0;

	int getNumberOfNodesEvaluated() {
		return _numOfNodes;
	};

	void increaseNumOfNodes() {
		this->_numOfNodes++;
	};
protected:
	void initialize(Searchable<Problem> *searchable) {
		for (auto vectorState:searchable->getStates()) {
			for (auto state:vectorState) {
				state->setDistanceFromSource(numeric_limits<int>::max());
				state->setColor(WHITE);
				state->setCameFrom(nullptr);
			}
		}
	}

	string makePath(State<Problem> *goalState) {
		string solution;
		State<Problem> *thisState = goalState;
		list<pair<int, int>> list;
		while (thisState != nullptr && thisState->getCameFrom() != nullptr) {
			State<Problem> *previous = thisState->getCameFrom();
			string toAppend = " (" + to_string(thisState->getDistanceFromSource()) + ")";
			string direction;
			int yCurrent = thisState->getLocation().second;
			int xCurrent = thisState->getLocation().first;
			int xPrevious = previous->getLocation().first;
			int yPrevious = previous->getLocation().second;

			if (yPrevious < yCurrent) {
				direction = ", Right";
			} else if (yPrevious == yCurrent) {
				if (xPrevious < xCurrent) {
					direction = ", Down";
				} else {
					direction = ", Up";
				}
			} else {
				direction = ", Left";
			}
			if (previous->getCameFrom() == nullptr) {
				direction.erase(direction.begin(), direction.begin() + 2);
			}
			solution.insert(0, toAppend);
			solution.insert(0, direction);

			thisState = previous;
		}
		solution.insert(0, "\n");
		solution.insert(0, to_string(this->_numOfNodes));
		solution.insert(0, "number of nodes: ");
		this->_numOfNodes = 0;
		return solution;
	}

};

#endif //SEARCHPROBLEMSOLVER_SEARCHER_H
