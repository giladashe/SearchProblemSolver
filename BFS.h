
#ifndef SEARCHPROBLEMSOLVER_BFS_H
#define SEARCHPROBLEMSOLVER_BFS_H


#include "Searcher.h"
#include <queue>

template<class Problem, class Solution>
class BFS : public Searcher<Problem, Solution> {

public:
	Solution search(Searchable<Problem> *searchable) override {
		enum Color {
			white = 1, gray, black
		};
		bool reachedGoal = false;
		//initialize the nodes
		Searcher<Problem, Solution>::initialize(searchable);
		State<Problem> *goalState = nullptr;
		//initialize the first node of the path
		State<Problem> * initial = searchable->getInitialState();
		initial->setDistanceFromSource(initial->getCost());
		searchable->getInitialState()->setColor(gray);
		//make queue for dfs algorithm
		queue <State<Problem>*> myQueue;
		myQueue.push(searchable->getInitialState());
		while (!myQueue.empty() && !reachedGoal) {
			State<Problem> *currentState = myQueue.front();
			myQueue.pop();
			for (auto state: searchable->getAllPossibleStates(currentState)) {
				//check if it wasn't visited / if it's not a wall
				if (state->getCost() != -1 && state->getColor() == white) {
					state->setColor(gray);
					state->setDistanceFromSource(currentState->getDistanceFromSource() + state->getCost());
					state->setCameFrom(currentState);
					myQueue.push(state);
					Searcher<Problem, Solution>::increaseNumOfNodes();
					//if reached the end ends loop
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

	//returns copy of the BFS algorithm
	Searcher<Problem, Solution> *clone() override {
		return new BFS<Problem, Solution>();
	}
};

#endif //SEARCHPROBLEMSOLVER_BFS_H
