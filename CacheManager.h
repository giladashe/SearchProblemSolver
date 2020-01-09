//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_CACHEMANAGER_H
#define SEARCHPROBLEMSOLVER_CACHEMANAGER_H

#include <string>

using namespace std;

class CacheManager {

public:
	virtual void insert(string key, string value) = 0;

	//checks if has it in cache or disk. if not - calculate solution and then insert.
	virtual string get(string key) = 0;

	virtual bool hasSolution(string problem) = 0;

};

#endif //SEARCHPROBLEMSOLVER_CACHEMANAGER_H
