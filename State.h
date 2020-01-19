
#ifndef SEARCHPROBLEMSOLVER_STATE_H
#define SEARCHPROBLEMSOLVER_STATE_H

#define WHITE 1

#include <string>
#include <limits>

using namespace std;

template<class Problem>
class State {
	pair<int, int> _location;
	double _cost = 0;
	int _color = WHITE;
	int _distanceFromSource = numeric_limits<int>::max();
	State<Problem> *_cameFrom = nullptr;
	int _hScore = 0;
	int _fScore = 0;
public:
	int getHScore() const {
		return _hScore;
	}

	int getFScore() const {
		return _fScore;
	}

	// Manhattan Distance
	void setHScore(State<Problem> *start, State<Problem> *end) {
		_hScore = abs(start->getLocation().first - end->getLocation().first)
				  + abs(start->getLocation().second - end->getLocation().second);
	}

	void setFScore(int fScore) {
		_fScore = fScore;
	}

	State<Problem>() = default;

	State<Problem>(const pair<int, int> &state, double cost) : _location(state), _cost(cost) {}

	const pair<int, int> &getLocation() const {
		return _location;
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

	/*friend bool operator>(const State &ls, const State &rs) {
		return ls.getCost() > rs.getCost();
	}*/
};

#endif //SEARCHPROBLEMSOLVER_STATE_H
