#ifndef SEARCHPROBLEMSOLVER_SOLVER_H
#define SEARCHPROBLEMSOLVER_SOLVER_H

template<class Problem, class Solution>
class Solver {

public:
	//solve the problem given
	virtual Solution solve(Problem problem) = 0;

	//make new specific Solver
	virtual Solver<Problem,Solution> *clone() = 0;

	virtual ~Solver()= default;
};


#endif //SEARCHPROBLEMSOLVER_SOLVER_H
