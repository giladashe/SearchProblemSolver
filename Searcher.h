//
// Created by giladasher on 13/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SEARCHER_H
#define SEARCHPROBLEMSOLVER_SEARCHER_H

#include "Searchable.h"

template<class Problem, class Solution>
class Searcher {
	int numOfNodes = 0;
public:
	virtual Solution search(Searchable<Problem> *searchable) = 0;

	virtual int getNumberOfNodesEvaluated() = 0;

	void increaseNumOfNodes() {
		this->numOfNodes++;
	};
};

#endif //SEARCHPROBLEMSOLVER_SEARCHER_H
