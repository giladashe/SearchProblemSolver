#ifndef SEARCHPROBLEMSOLVER_SOLVER_H
#define SEARCHPROBLEMSOLVER_SOLVER_H

template<class Problem, class Solution>
class Solver {

public:
	Solution solve(Problem problem) = 0;
};


#endif //SEARCHPROBLEMSOLVER_SOLVER_H
