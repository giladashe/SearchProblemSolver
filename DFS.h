
#ifndef SEARCHPROBLEMSOLVER_DFS_H
#define SEARCHPROBLEMSOLVER_DFS_H

#include "Searcher.h"
#include <stack>

template<class Problem, class Solution>
class DFS : public Searcher<Problem, Solution> {
public:
	Solution search(Searchable<Problem> *searchable) override {
		enum Color {
			white = 1, gray, black
		};
		bool reachedGoal = false;
		//initialize the nodes
		Searcher<Problem, Solution>::initialize(searchable);
		//initialize the first node of the path
		State<Problem> *initial = searchable->getInitialState();
		initial->setDistanceFromSource(initial->getCost());
		initial->setColor(gray);
		//make stack for dfs algorithm
		stack < State<Problem> * > myStack;
		myStack.push(initial);
		State<Problem> *goalState = nullptr;
		while (!myStack.empty() && !reachedGoal) {
			State<Problem> *stateOnTop = myStack.top();
			myStack.pop();
			for (auto currentState: searchable->getAllPossibleStates(stateOnTop)) {
				if (currentState->getCost() != -1 && currentState->getColor() == white) {
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
