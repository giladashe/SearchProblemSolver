
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
            white = 1, black
        };
		State<Problem>* initialState = searchable->getInitialState();
		initialState->setDistanceFromSource(initialState->getCost());
        priority_queue<State<Problem>*, vector<State<Problem>*>, DistanceCompare> pqueue_D;//
        pqueue_D.push(searchable->getInitialState());

        while (!pqueue_D.empty()) {
            State<Problem> *currentState = pqueue_D.top();
            if (searchable->isGoalState(currentState)) {
                goalState = currentState;
                return Searcher<Problem, Solution>::makePath(goalState);
            }
            pqueue_D.pop();
            currentState->setColor(black);
            // for each neighbor of current
            for (auto state: searchable->getAllPossibleStates(currentState)) {
                if (state->getCost() != -1 && (state->getColor() == white)){
                    // tentative Gscore
                    int tentativeGscore = currentState->getDistanceFromSource()
                                          + state->getCost();
                    if (state->getColor() == black || tentativeGscore >= state->getDistanceFromSource()){
                        continue;
                    }
                    // check if neighbor is in pqueue_F
                    bool neighborNotInPqueue_F = true;

                    vector<State<Problem>*> temporaryVector;
                    while (!pqueue_D.empty()){
                        State<Problem>* curr = pqueue_D.top();
                        temporaryVector.push_back(curr);
                        if (state == curr){
                            neighborNotInPqueue_F = false;
                        }
                        pqueue_D.pop();
                    }
                    // return the elements to pqueue_F
                    for (auto it = temporaryVector.cbegin(); it!=temporaryVector.cend(); it++)
                    {
                        pqueue_D.push(*it);
                    }
                    if (neighborNotInPqueue_F || tentativeGscore < state->getDistanceFromSource()){
                        Searcher<Problem, Solution>::increaseNumOfNodes();
                        state->setCameFrom(currentState);
                        state->setDistanceFromSource(tentativeGscore);
                        if (neighborNotInPqueue_F) {
                            pqueue_D.push(state);
                        }
                    }
                }
            }
        }
	}

    struct DistanceCompare
    {
        bool operator()(State<Problem>* ls, State<Problem>* rs)
        {
            return  ls->getDistanceFromSource() > rs->getDistanceFromSource();
        }
    };

    Searcher<Problem, Solution> *clone() override {
		return new BestFirstSearch<Problem, Solution>();
	}
};


#endif //SEARCHPROBLEMSOLVER_BESTFIRSTSEARCH_H
