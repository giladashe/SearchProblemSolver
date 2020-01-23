

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
        Solution solution = this->_searcher->search(matrix);
        delete matrix;
		return solution;
	}

	Solver<Problem, Solution> *clone() override {
		return new SearchSolver<Problem, Solution>(_searcher->clone());
	}

	~SearchSolver() override  {
		delete this->_searcher;
	}
};


#endif //SEARCHPROBLEMSOLVER_SEARCHSOLVER_H
