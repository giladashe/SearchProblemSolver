#ifndef SEARCHPROBLEMSOLVER_CACHEMANAGER_H
#define SEARCHPROBLEMSOLVER_CACHEMANAGER_H

#include <string>

using namespace std;

template<class Problem, class Solution>
class CacheManager {

public:
	virtual ~CacheManager() = default;

	//save the solution in the cache
	virtual void saveSolution(Problem problem, Solution solution) = 0;

	//get solution from cache
	virtual Solution getSolution(Problem problem) = 0;

	//checks if has the solution in cache
	virtual bool hasSolution(Problem problem) = 0;

	virtual CacheManager *clone() = 0;
};

#endif //SEARCHPROBLEMSOLVER_CACHEMANAGER_H
