//
// Created by giladasher on 13/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SEARCHSOLVER_H
#define SEARCHPROBLEMSOLVER_SEARCHSOLVER_H

#include "Solver.h"
#include "Searcher.h"

template<class Problem, class Solution>
class SearchSolver : public Solver<Problem, Solution> {
	Searcher<Problem, Solution> *searcher;

public:
	SearchSolver(Searcher<Problem, Solution> *searcher) : searcher(searcher) {};

	Solution solve(Searchable<Problem>* problem) override {
		return this->searcher->search(problem);
	}

};


#endif //SEARCHPROBLEMSOLVER_SEARCHSOLVER_H
