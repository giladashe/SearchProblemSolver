//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_DFS_H
#define SEARCHPROBLEMSOLVER_DFS_H

#include "Searcher.h"

template<class Problem, class Solution>
class DFS : public Searcher<Problem, Solution> {
public:
	Solution search(Searchable<Problem> *searchable) override {
		return nullptr;
	}

	int getNumberOfNodesEvaluated() override {
		return 0;
	}

};

#endif //SEARCHPROBLEMSOLVER_DFS_H
