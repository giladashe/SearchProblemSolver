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

	void initialize(Searchable<Problem> *searchable) {
		for (auto vectorState:searchable->getStates()) {
			for (auto state:vectorState) {
				state->setDistanceFromSource(numeric_limits<int>::max());
				state->setColor(WHITE);
				state->setCameFrom(nullptr);
			}

		}
	}
};

#endif //SEARCHPROBLEMSOLVER_SEARCHER_H
