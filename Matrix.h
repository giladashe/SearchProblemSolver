#ifndef SEARCHPROBLEMSOLVER_MATRIX_H
#define SEARCHPROBLEMSOLVER_MATRIX_H

#include "Searchable.h"
#include <algorithm>

template<class Problem>
class Matrix : public Searchable<Problem> {
	vector<vector<State<Problem> *>> _states;
	State<Problem> *_initialState;
	vector<State<Problem> *> _goalStates;
	int _rows = 0;
	int _columns = 0;

	bool inRange(int i, int j) {
		return i >= 0 && i < _rows && j >= 0 && j < _columns;
	}

public:
	//split a string by a delimiter
	static vector<string> splitByDelimiter(string &s, const string &delimiter) {
		//based on https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
		size_t pos = 0;
		string copyOfStr = string(s);
		string token;
		vector<string> splitString;
		while ((pos = copyOfStr.find(delimiter)) != string::npos) {
			token = copyOfStr.substr(0, pos);
			copyOfStr.erase(0, pos + delimiter.length());
			splitString.push_back(token);
		}
		splitString.push_back(copyOfStr);
		return splitString;
	}

	Matrix(string matrixStr) {
		//makes matrix from str
		bool hasCols = false;
		bool hasInitial = false;
		// the x,y pair of location
		int first = 0;
		int second = 0;
		//split by lines
		vector<string> splitLines = Matrix::splitByDelimiter(matrixStr, "\n");
		vector<string> splitByComma;
		//go over all the lines and
		for (auto &splitLine : splitLines) {
			splitLine.erase(remove(splitLine.begin(), splitLine.end(), ' '), splitLine.end());
			splitLine.erase(remove(splitLine.begin(), splitLine.end(), '\t'), splitLine.end());
			splitByComma = Matrix::splitByDelimiter(splitLine, ",");
			if (splitByComma.size() < 2) {
				continue;
			}
			if (!hasCols) {
				this->_columns = splitByComma.size();
				hasCols = true;
			}
			if (splitByComma.size() != this->_columns) {
				if (!hasInitial) {
					//we are in the line of the point of start
					first = stoi(splitByComma[0]);
					second = stoi(splitByComma[1]);
					this->_initialState = this->_states[first][second];
					hasInitial = true;
				} else {
					//we're in the line of the goal point
					first = stoi(splitByComma[0]);
					second = stoi(splitByComma[1]);
					this->_goalStates.push_back(this->_states[first][second]);
				}
			} else {
				//make a line of the matrix
				vector<State<Problem> *> rowStates;
				int row = this->_rows;
				for (int j = 0; j < this->_columns; j++) {
					auto *state = new State<Problem>(make_pair(row, j), stoi(splitByComma[j]));
					rowStates.push_back(state);
				}
				//insert line to lines of the matrix
				this->_states.push_back(rowStates);
				this->_rows++;
			}
			splitByComma.clear();
		}
	}

	State<Problem> *getInitialState() override {
		return this->_initialState;
	}

	bool isGoalState(const State<Problem> *state) override {
		bool isGoal = false;
		for (auto &currentState:_goalStates) {
			//they both point on goal
			if (currentState == state) {
				isGoal = true;
			}
		}
		return isGoal;
	}

	vector<State<Problem> *> getAllPossibleStates(State<Problem> *state) override {
		//get all possible states you can go from given state (using range of the matrix)
		vector<State<Problem> *> possibleStates;
		int stateX = state->getLocation().first;
		int stateY = state->getLocation().second;
		int counterX = stateX - 1;
		int counterY = stateY;
		// down, up, right, left
		if (this->inRange(stateX + 1, stateY)) {
			possibleStates.push_back(_states[stateX + 1][stateY]);
		}
		if (this->inRange(stateX - 1, stateY)) {
			possibleStates.push_back(_states[stateX - 1][stateY]);
		}
		if (this->inRange(stateX, stateY + 1)) {
			possibleStates.push_back(_states[stateX][stateY + 1]);
		}
		if (this->inRange(stateX, stateY - 1)) {
			possibleStates.push_back(_states[stateX][stateY - 1]);
		}
		return possibleStates;
	}

	vector<vector<State<Problem> *>> getStates() override {
		return _states;
	}

	vector<State<Problem> *> getGoalStates() override {
		return _goalStates;
	}


};

#endif //SEARCHPROBLEMSOLVER_MATRIX_H
