//
// Created by giladasher on 08/01/2020.
//

#include "FileCacheManager.h"

bool FileCacheManager::hasSolution(string problem) {
	//if it has the problem in cache returns true and otherwise false
	return this->_cacheMap.find(problem) != this->_cacheMap.end();
}
