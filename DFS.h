//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_DFS_H
#define SEARCHPROBLEMSOLVER_DFS_H

#include "Searcher.h"
#include <stack>

template<class Problem, class Solution>
class DFS : public Searcher<Problem, Solution> {
public:
	Solution search(Searchable<Problem> *searchable) override {
		stack < State<Problem> * > myStack;
		Searcher<Problem, Solution>::initialize(searchable);
		State<Problem> *initial = searchable->getInitialState();
		initial->setDistanceFromSource(initial->getCost());
		enum Color {
			white = 1, gray, black
		};
		initial->setColor(gray);
		myStack.push(searchable->getInitialState());
		bool reachedGoal = false;
		State<Problem> *goalState = nullptr;
		while (!myStack.empty() && !reachedGoal) {
			State<Problem> *stateOnTop = myStack.top();
			myStack.pop();
			for (auto currentState: searchable->getAllPossibleStates(stateOnTop)) {
				if (currentState->getCost() != -1 && currentState->getColor() == WHITE) {
					currentState->setColor(gray);
					currentState->setDistanceFromSource(stateOnTop->getDistanceFromSource() + currentState->getCost());
					currentState->setCameFrom(stateOnTop);
					Searcher<Problem, Solution>::increaseNumOfNodes();
					if (searchable->isGoalState(currentState)) {
						goalState = currentState;
						reachedGoal = true;
						break;
					}
					myStack.push(currentState);
				}
			}
			stateOnTop->setColor(black);
		}
		return Searcher<Problem, Solution>::makePath(goalState);
	}

	Searcher<Problem, Solution> *clone() override {
		return new DFS<Problem, Solution>();
	}
};

#endif //SEARCHPROBLEMSOLVER_DFS_H
