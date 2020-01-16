//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_ASTAR_H
#define SEARCHPROBLEMSOLVER_ASTAR_H

#include "Searcher.h"
#include <queue>
#include <vector>

template<class Problem, class Solution>
class AStar : public Searcher<Problem, Solution> {
public:
	Solution search(Searchable<Problem> *searchable) override {
        Searcher<Problem, Solution>::initialize(searchable);
        State<Problem> *goalState = nullptr;
        bool reachedGoal = false;
        enum Color {
            white = 1, black
        };
        State<Problem>* initialState = searchable->getInitialState();
        initialState->setDistanceFromSource(0);
        // priority queue by minimal f = DistanceFromSource + h
        priority_queue<State<Problem>*, vector<State<Problem>*>, FCompare> pqueue_F;//
        pqueue_F.push(initialState);
        // setF for initial state
        initialState->setHScore(initialState,searchable->getGoalStates().at(0));
        initialState->setFScore(initialState->getHScore());
        while (!pqueue_F.empty()) {
            State<Problem> *currentState = pqueue_F.top();
            if (searchable->isGoalState(currentState)) {
                goalState = currentState;
                return Searcher<Problem, Solution>::makePath(goalState);
            }
            pqueue_F.pop();
            currentState->setColor(black);
            // for each neighbor of current
            for (auto state: searchable->getAllPossibleStates(currentState)) {
                if (state->getCost() != -1){
                    Searcher<Problem, Solution>::increaseNumOfNodes();
                    // tentative Gscore
                    int tentativeGscore = currentState->getDistanceFromSource()
                                          + state->getCost();
                    if (state->getColor() == black || tentativeGscore >= state->getDistanceFromSource()){
                        continue;
                    }
                    // check if neighbor is in pqueue_F
                    bool neighborNotInPqueue_F = true;

                    vector<State<Problem>*> temporaryVector;
                    while (!pqueue_F.empty()){
                        State<Problem>* curr = pqueue_F.top();
                        temporaryVector.push_back(curr);
                        if (state == curr){
                            neighborNotInPqueue_F = false;
                        }
                        pqueue_F.pop();
                    }
                    // return the elements to pqueue_F
                    for (auto it = temporaryVector.cbegin(); it!=temporaryVector.cend(); it++)
                    {
                        pqueue_F.push(*it);
                    }
                    if (neighborNotInPqueue_F || tentativeGscore < state->getDistanceFromSource()){
                        state->setCameFrom(currentState);
                        state->setDistanceFromSource(tentativeGscore);
                        state->setHScore(state,searchable->getGoalStates().at(0));
                        state->setFScore(state->getDistanceFromSource() + state->getHScore());
                        if (neighborNotInPqueue_F) {
                            pqueue_F.push(state);
                        }
                    }
                }
            }
        }
	}

    struct FCompare
    {
        bool operator()(State<Problem>* ls, State<Problem>* rs)
        {
            return  ls->getFScore() > rs->getFScore();
        }
    };

};

#endif //SEARCHPROBLEMSOLVER_ASTAR_H
