//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_CACHEMANAGER_H
#define SEARCHPROBLEMSOLVER_CACHEMANAGER_H

#include <string>

using namespace std;

template<class Problem, class Solution>
class CacheManager {

public:
	virtual void saveSolution(Problem problem, Solution solution) = 0;

	//checks if has it in cache or disk. if not - calculate solution and then saveSolution.
	virtual Solution getSolution(Problem problem) = 0;

	virtual bool hasSolution(Problem problem) = 0;

};

#endif //SEARCHPROBLEMSOLVER_CACHEMANAGER_H
