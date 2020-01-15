//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_BFS_H
#define SEARCHPROBLEMSOLVER_BFS_H


#include "Searcher.h"
#include <queue>

template<class Problem, class Solution>
class BFS : public Searcher<Problem, Solution> {

public:
	Solution search(Searchable<Problem> *searchable) override {
		Searcher<Problem, Solution>::initialize(searchable);
		State<Problem> *goalState = nullptr;
		bool reachedGoal = false;
		enum Color {
			white = 1, gray, black
		};
		searchable->getInitialState()->setDistanceFromSource(0);
		searchable->getInitialState()->setColor(gray);
		queue < State<Problem>*> myQueue;
		myQueue.push(searchable->getInitialState());
		while (!myQueue.empty() && !reachedGoal) {
			State<Problem> *currentState = myQueue.front();
			myQueue.pop();
			for (auto state: searchable->getAllPossibleStates(currentState)) {
				if (state->getCost() != -1 && state->getColor() == white) {
					state->setColor(gray);
					state->setDistanceFromSource(currentState->getDistanceFromSource() + 1);
					state->setCameFrom(currentState);
					myQueue.push(state);
					Searcher<Problem, Solution>::increaseNumOfNodes();
					if (searchable->isGoalState(state)) {
						goalState = state;
						reachedGoal = true;
						break;
					}
				}
			}
			currentState->setColor(black);
		}

		State<Problem> *thisState = goalState;
		return Searcher<Problem, Solution>::makePath(goalState);
	}


};

#endif //SEARCHPROBLEMSOLVER_BFS_H
