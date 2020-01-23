

#ifndef SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H
#define SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H

#include <unordered_map>
#include <list>
#include <fstream>
#include <mutex>
#include "CacheManager.h"


template<class Problem, class Solution>
class FileCacheManager : public CacheManager<Problem, Solution> {
	list <Problem> lru;
	int size = 15;
	unordered_map<Problem, pair<Solution, typename list<Problem>::iterator>> cache;
public:

	void saveSolution(Problem problem, Solution solution) override {

		//making hash of the string so it won't be long
		hash<Problem> myHash;
		int hashForFile = myHash(problem);
		string hashProblemStr = to_string(hashForFile);
		auto objIter = this->cache.find(hashProblemStr);
		//obj not in cache
		if (objIter != this->cache.end()) {
			throw "already in map";
		}

		//obj in disk
		if (fileExists(hashProblemStr)) {
			throw "already exists";
		}
		ofstream ofStream1;
		ofStream1.open(hashProblemStr, ios::binary);
		ofStream1 << solution;
		ofStream1.close();

		//change LRU because size is too big
		if (this->cache.size() == (unsigned) this->size) {
			auto last = this->lru.back();
			this->lru.pop_back();
			this->cache.erase(last);
		}
		//insert to cache and lru
		this->lru.push_front(hashProblemStr);
		this->cache.insert(make_pair(hashProblemStr, make_pair(solution, this->lru.begin())));
	}

	//get solution from cache - map or file
	Solution getSolution(Problem problem) override {
		//check hash of string - name of the file and key
		hash<string> myHash;
		int hashForFile = myHash(problem);
		string hashProblemStr = to_string(hashForFile);
		auto objIter = this->cache.find(hashProblemStr);
		//obj not in cache
		if (objIter == this->cache.end()) {
			if (!fileExists(hashProblemStr)) {
				throw "an error";
			}
			ifstream ifStream1;
			ifStream1.open(hashProblemStr, ios::binary);
			if (!ifStream1.is_open()) {
				throw "error opening file";
			}
			Solution solution;
			Solution line;
			while (getline(ifStream1, line)) {
				solution += line;
			}
			ifStream1.close();
			if (this->cache.size() == (unsigned) this->size) {
				auto last = this->lru.back();
				this->lru.pop_back();
				this->cache.erase(last);
			}
			this->lru.push_front(hashProblemStr);
			this->cache.insert(make_pair(hashProblemStr, make_pair(solution, this->lru.begin())));
			return solution;
		} else { //found object in cash - put it in the front of list and return it
			if (this->lru.size() > 1) {
				auto position = objIter->second.second;
				this->lru.erase(position);
				this->lru.push_front(objIter->first);
			}
			auto cacheSolution = objIter->second.first;
			return cacheSolution;
		}
	}

	bool hasSolution(Problem problem) override {
		//check hash of string - name of the file and the key
		hash<string> myHash;
		int hashForFile = myHash(problem);
		string hashProblemStr = to_string(hashForFile);
		auto objIter = this->cache.find(hashProblemStr);
		//obj not in map of cache
		if (objIter == this->cache.end()) {
			//obj not in disk
			if (!fileExists(hashProblemStr)) {
				return false;
			}
		}
		return true;
	}

	bool fileExists(const string &filename) {
		ifstream iFile(filename.c_str());
		return (bool) iFile;
	}

	CacheManager<Problem, Solution> *clone() override {
		return new FileCacheManager<Problem, Solution>;
	}
};


#endif //SEARCHPROBLEMSOLVER_FILECACHEMANAGER_H
