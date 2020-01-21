//
// Created by giladasher on 13/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SEARCHSOLVER_H
#define SEARCHPROBLEMSOLVER_SEARCHSOLVER_H

#include "Solver.h"
#include "Searcher.h"

template<class Problem, class Solution>
class SearchSolver : public Solver<Problem, Solution> {
	Searcher<Problem, Solution> *_searcher;

public:
	SearchSolver(Searcher<Problem, Solution> *searcher) : _searcher(searcher) {};

	Solution solve(Problem problem) override {
        Searchable<Problem>* matrix = new Matrix<Problem>(problem);
		return this->searcher->search(matrix);
	}

	Solver<Problem, Solution> *clone() override {
		return new SearchSolver<Problem, Solution>(_searcher->clone());
	}
};


#endif //SEARCHPROBLEMSOLVER_SEARCHSOLVER_H
