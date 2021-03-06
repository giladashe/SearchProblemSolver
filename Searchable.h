

#ifndef SEARCHPROBLEMSOLVER_SEARCHABLE_H
#define SEARCHPROBLEMSOLVER_SEARCHABLE_H

#include "State.h"
#include <vector>

using namespace std;

template<class Problem>
class Searchable {

public:
	virtual ~Searchable() = default;

	virtual State<Problem>* getInitialState() = 0;

	virtual bool isGoalState(const State<Problem>* state) = 0;

	virtual vector<State<Problem>*> getAllPossibleStates(State<Problem> *state) = 0;

	virtual vector<vector<State<Problem>*>> getStates()=0;

    virtual vector<State<Problem>*> getGoalStates() = 0;
};

#endif //SEARCHPROBLEMSOLVER_SEARCHABLE_H
