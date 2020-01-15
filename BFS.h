//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_BFS_H
#define SEARCHPROBLEMSOLVER_BFS_H

#define WHITE 1
#define GRAY 2
#define BLACK 3

#include "Searcher.h"
#include <queue>

template<class Problem, class Solution>
class BFS : public Searcher<Problem, Solution> {


public:
	Solution search(Searchable<Problem> *searchable) override {
		Searcher<Problem, Solution>::initialize(searchable);
		State<Problem> *goalState = nullptr;
		searchable->getInitialState()->setDistanceFromSource(0);
		searchable->getInitialState()->setColor(GRAY);
		queue < State<Problem> * > myQueue;
		myQueue.push(searchable->getInitialState());
		while (!myQueue.empty()) {
			State<Problem> *currentState = myQueue.front();
			myQueue.pop();
			for (auto state: searchable->getAllPossibleStates(currentState)) {
				if (state->getCost() != -1 && state->getColor() == WHITE) {
					state->setColor(GRAY);
					state->setDistanceFromSource(currentState->getDistanceFromSource() + 1);
					state->setCameFrom(currentState);
					myQueue.push(state);
					Searcher<Problem, Solution>::increaseNumOfNodes();
					if (searchable->isGoalState(state)) {
						goalState = state;

						while (!myQueue.empty()) {
							myQueue.pop();
						}

						break;
					}
				}
			}
			currentState->setColor(BLACK);
		}

		string solution;
		State<Problem> *thisState = goalState;
		while (thisState != nullptr && thisState->getCameFrom() != nullptr) {
			State<Problem> *previous = thisState->getCameFrom();
			string toAppend = " (" + to_string(thisState->getDistanceFromSource()) + ")";
			string direction;
			int yCurrent = thisState->getState().second;
			int xCurrent = thisState->getState().first;
			int xPrevious = previous->getState().first;
			int yPrevious = previous->getState().second;

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

#endif //SEARCHPROBLEMSOLVER_BFS_H
