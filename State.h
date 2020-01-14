
#ifndef SEARCHPROBLEMSOLVER_STATE_H
#define SEARCHPROBLEMSOLVER_STATE_H

#include <string>

using namespace std;

template<class Problem>
class State {
	pair<int, int> _state;
	double _cost;
	State<Problem> *_cameFrom = nullptr;
public:

	State(const pair<int, int> &state, double cost) : _state(state), _cost(cost) {}

	const pair<int, int> &getState() const {
		return _state;
	}

	double getCost() const {
		return _cost;
	}

	void setCameFrom(const State<Problem> &cameFrom) {
		this->_cameFrom = cameFrom;
	}

	bool operator==(const State<Problem> &other) {
		return this->_state == other.getState() && this->_cost == other.getCost();
	}

};

#endif //SEARCHPROBLEMSOLVER_STATE_H
