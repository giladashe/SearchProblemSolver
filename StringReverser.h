

#ifndef SEARCHPROBLEMSOLVER_STRINGREVERSER_H
#define SEARCHPROBLEMSOLVER_STRINGREVERSER_H

#include <string>
#include "Solver.h"

using namespace std;

template<class Problem, class Solution>
class StringReverser : public Solver<Problem, Solution> {
	//get a string and make new reversed string
	Solution solve(Problem problem) override {
		string solution;
		string problemStr(problem);
		int i;
		for (i = (int) problemStr.length() - 1; i >= 0; i--) {
			solution += problemStr[i];
		}
		return solution;
	}
};

#endif //SEARCHPROBLEMSOLVER_STRINGREVERSER_H
