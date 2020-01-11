//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H
#define SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H

#include <unordered_map>
#include <list>
#include <fstream>
#include "CacheManager.h"

template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
	list <Problem> lru;
	int size = 5;
	unordered_map<Problem, pair<Solution, typename list<Problem>::iterator>> cache;
public:

	void saveSolution(Problem problem, Solution solution) override {
		auto objIter = this->cache.find(problem);
		//obj not in cache
		if (objIter != this->cache.end()) {
			throw "already in map";
		}
		ofstream ofStream1;
		//obj in disk
		if (fileExists(problem)) {
			throw "already exists";
		}
		ofStream1.open(problem, ios::binary);
		ofStream1.write((char *) &solution, sizeof(solution));
		ofStream1.close();

		//change LRU because size is too big
		if (this->cache.size() == (unsigned) this->size) {
			auto last = this->lru.back();
			this->lru.pop_back();
			this->cache.erase(last);
		}
		//insert to cache and lru
		this->lru.push_front(problem);
		this->cache.insert(make_pair(problem, make_pair(solution, this->lru.begin())));
	}

	//get solution from cache - map or file
	Solution getSolution(Problem problem) override {
		auto objIter = this->cache.find(problem);
		//obj not in cache
		if (objIter == this->cache.end()) {
			ifstream ifStream1;
			hash<string> myHash;

			// Using operator() to get hash value

			int hashForFile = myHash(problem);

			if (!fileExists(problem)) {
				throw "an error";
			}
			ifStream1.open(problem, ios::binary);
			if (!ifStream1.is_open()) {
				throw "error opening file";
			}
			Solution solution;
			ifStream1.read((char *) &solution, sizeof(solution));
			if (this->cache.size() == (unsigned) this->size) {
				auto last = this->lru.back();
				this->lru.pop_back();
				this->cache.erase(last);
			}
			this->lru.push_front(problem);
			this->cache.insert(make_pair(problem, make_pair(solution, this->lru.begin())));
			ifStream1.close();

			return solution;
		} else { //found object in cash - put it in the front of list and return it
			auto position = objIter->second.second;
			this->lru.erase(position);
			this->lru.push_front(objIter->first);
			return objIter->second.first;
		}
	}

	bool hasSolution(Problem problem) override {
		auto objIter = this->cache.find(problem);
		//obj not in map of cache
		if (objIter == this->cache.end()) {
			ofstream ofStream1;
			//obj in disk
			if (!this->fileExists(problem)) {
				return false;
			}
		}
		return true;
	}

	bool fileExists(const string &filename) {
		ifstream iFile(filename.c_str());
		return (bool) iFile;
	}

};


#endif //SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H
