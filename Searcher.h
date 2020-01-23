

#ifndef SEARCHPROBLEMSOLVER_SEARCHER_H
#define SEARCHPROBLEMSOLVER_SEARCHER_H

#include "Searchable.h"

template<class Problem, class Solution>
class Searcher {
	int _numOfNodes = 0;
public:
	virtual ~Searcher() = default;

	virtual Solution search(Searchable<Problem> *searchable) = 0;

	int getNumberOfNodesEvaluated() {
		return _numOfNodes;
	};

	void increaseNumOfNodes() {
		this->_numOfNodes++;
	};

	virtual Searcher<Problem, Solution> *clone() = 0;

protected:
	//initialize the nodes of the searchable object
	void initialize(Searchable<Problem> *searchable) {
		//reset number of nodes evaluated
		this->_numOfNodes = 0;
		for (auto vectorState:searchable->getStates()) {
			for (auto state:vectorState) {
				state->setDistanceFromSource(numeric_limits<int>::max());
				state->setColor(WHITE);
				state->setCameFrom(nullptr);
			}
		}
	}

	//make string for the path of the solution from goal state to initial state
	string makePath(State<Problem> *goalState) {
		string solution;
		State<Problem> *thisState = goalState;
		list<pair<int, int>> list;
		while (thisState != nullptr && thisState->getCameFrom() != nullptr) {
			//write the sum of path from initial state to goal state
			State<Problem> *previous = thisState->getCameFrom();
			string toAppend = " (" + to_string(thisState->getDistanceFromSource()) + ")";
			string direction;
			int yCurrent = thisState->getLocation().second;
			int xCurrent = thisState->getLocation().first;
			int xPrevious = previous->getLocation().first;
			int yPrevious = previous->getLocation().second;

			//write the directions (from the beginning)
			if (yPrevious < yCurrent) {
				direction = ", Right";
			} else if (yPrevious == yCurrent) {
				if (xPrevious < xCurrent) {
					direction = ", Down";
				} else {
					direction = ", Up";
				}
			} else {
				direction = ", Left";
			}
			//erase the space and comma from beginning of the string
			if (previous->getCameFrom() == nullptr) {
				direction.erase(direction.begin(), direction.begin() + 2);
			}
			solution.insert(0, toAppend);
			solution.insert(0, direction);

			thisState = previous;
		}
		return solution;
	}

};

#endif //SEARCHPROBLEMSOLVER_SEARCHER_H
