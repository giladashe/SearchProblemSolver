#ifndef SEARCHPROBLEMSOLVER_SOLVER_H
#define SEARCHPROBLEMSOLVER_SOLVER_H

template<class Problem, class Solution>
class Solver {

public:
	virtual Solution solve(Problem problem) = 0;

	virtual Solver<Problem,Solution> *clone() = 0;
};


#endif //SEARCHPROBLEMSOLVER_SOLVER_H
