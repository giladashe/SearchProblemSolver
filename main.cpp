#include <iostream>
#include "FileCacheManager.h"
#include "StringReverser.h"

using namespace std;

int main() {
	CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
	Solver<string, string> *solver = new StringReverser<string, string>();
	cacheManager->saveSolution("abc", "cba");
	cacheManager->getSolution("abc");

	cacheManager->saveSolution("that", "taht");
	cacheManager->saveSolution("567", "765");
	cacheManager->saveSolution("just", "tsuj");
	cacheManager->saveSolution("run", "nur");
	cacheManager->saveSolution("lsd", "dls");

	string solution;
	if (cacheManager->hasSolution("abc")) {
		solution = cacheManager->getSolution("abc");
	} else {
		solution = solver->solve("abc");
	}
	cout<<solution<<endl;
	if (cacheManager->hasSolution("what's going on?, fine!")) {
		solution = cacheManager->getSolution("what's going on?, fine!");
	} else {
		solution = solver->solve("what's going on?, fine!");
		cacheManager->saveSolution("what's going on?, fine!", solution);
	}
	cout<<solution<<endl;
	return 0;
}