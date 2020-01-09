//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H
#define SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H

#include <unordered_map>
#include "CacheManager.h"

class FileCacheManager : public CacheManager {
	unordered_map<string ,string > _cacheMap;

	bool fileExists(const string &filename);

public:
	void insert(string key, string value) override;

	//checks if has it in cache or disk. if not - calculate solution and then insert.
	string get(string key) override;

	bool hasSolution(string problem) override;

};


#endif //SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H
