
#ifndef SEARCHPROBLEMSOLVER_STATE_H
#define SEARCHPROBLEMSOLVER_STATE_H

#define WHITE 1

#include <string>
#include <limits>

using namespace std;

template<class Problem>
class State {
	pair<int, int> _state;
	double _cost = 0;
	int _color = WHITE;
	int _distanceFromSource = numeric_limits<int>::max();
	State<Problem> *_cameFrom = nullptr;
public:

	State<Problem>() = default;

	State<Problem>(const pair<int, int> &state, double cost) : _state(state), _cost(cost) {}

	const pair<int, int> &getState() const {
		return _state;
	}

	double getCost() const {
		return _cost;
	}

	void setCameFrom(State<Problem> *cameFrom) {
		this->_cameFrom = cameFrom;
	}

	void setColor(int color) {
		_color = color;
	}

	void setDistanceFromSource(int distanceFromSource) {
		_distanceFromSource = distanceFromSource;
	}

	int getColor() const {
		return _color;
	}

	int getDistanceFromSource() const {
		return _distanceFromSource;
	}

	State<Problem> *getCameFrom() const {
		return _cameFrom;
	}
};

#endif //SEARCHPROBLEMSOLVER_STATE_H
