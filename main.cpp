#include <iostream>
#include "FileCacheManager.h"
#include "StringReverser.h"
using namespace std;
int main()
{
	CacheManager<const char*, const char*> *cacheManager = new FileCacheManager<const char*, const char*>();
	//Solver<int,int>* solver = new StringReverser<int,int>();
	cacheManager->saveSolution("1", "2");
	cacheManager->saveSolution("3","4");
	cacheManager->saveSolution("5", "6");
	cacheManager->saveSolution("7", "8");
	cacheManager->saveSolution("9", "10");
	cacheManager->saveSolution("11", "12");

	const char* solution;
	if (cacheManager->hasSolution("1")) {
		solution = cacheManager->getSolution("1");
	} else {
	//	solution = solver->solve(3);
	}
	return 0;
}