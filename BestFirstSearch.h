
#ifndef SEARCHPROBLEMSOLVER_BESTFIRSTSEARCH_H
#define SEARCHPROBLEMSOLVER_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include <queue>
#include <vector>

template <class Problem,class Solution>
class BestFirstSearch: public Searcher<Problem,Solution>{
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
        priority_queue<State<Problem>*, vector<State<Problem>*>, greater<typename vector<State<Problem>*>::value_type>> pqueue_greater;//
        pqueue_greater.push(searchable->getInitialState());
        while (!pqueue_greater.empty() && !reachedGoal) {
            State<Problem> *currentState = pqueue_greater.top();
            pqueue_greater.pop();
            for (auto state: searchable->getAllPossibleStates(currentState)) {
                if (state->getCost() != -1 && state->getColor() == white) {
                    state->setColor(gray);
                    state->setDistanceFromSource(currentState->getDistanceFromSource() + state->getCost());
                    state->setCameFrom(currentState);
                    pqueue_greater.push(state);
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


#endif //SEARCHPROBLEMSOLVER_BESTFIRSTSEARCH_H
