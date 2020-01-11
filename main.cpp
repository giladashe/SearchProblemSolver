#include <iostream>
#include "CacheManager.h"
#include "FileCacheManager.h"

int main() {
	CacheManager<string,string> *cacheManager = new FileCacheManager<string,string>();
	cacheManager->saveSolution("something", "asfdgrsfasd");
	string solution;
	if (cacheManager->hasSolution("something")) {
		solution = cacheManager->getSolution("something");
	} else {
		cout << "something" << endl;
	}

	return 0;
}
