//
// Created by giladasher on 14/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_MATRIX_H
#define SEARCHPROBLEMSOLVER_MATRIX_H

#include "Searchable.h"
#include <algorithm>

template<class Problem>
class Matrix : public Searchable<Problem> {
	vector<vector<State<Problem>>> _states;
	State<Problem> _initialState;
	vector<State<Problem>> _goalStates;
	int _rows;
	int _columns;

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
		//todo make matrix from str
		bool hasCols = false;
		bool hasInitial = false;
		int first = 0;
		int second = 0;
		int rows = 0;
		vector<string> splitLines = Matrix::splitByDelimiter(matrixStr, "\n");
		vector<string> splitByComma;
		for (auto &splitLine : splitLines) {
			splitLine.erase(remove(splitLine.begin(), splitLine.end(), ' '), splitLine.end());
			splitLine.erase(remove(splitLine.begin(), splitLine.end(), '\t'), splitLine.end());
			splitByComma = Matrix::splitByDelimiter(splitLine, ",");
			if (!hasCols && !splitByComma.empty()) {
				this->_columns = splitByComma.size();
				hasCols = true;
			} else if (splitByComma.size() != this->_columns) {
				if (splitByComma.empty()) {
					continue;
				} else if (!hasInitial) {
					this->_rows = rows;
					//todo initial
					first = stoi(splitByComma[0]);
					second = stoi(splitByComma[1]);
					this->_initialState = this->_states[first][second];
					hasInitial = true;
				} else {
					//todo goal
					first = stoi(splitByComma[0]);
					second = stoi(splitByComma[1]);
					this->_goalStates.push_back(this->_states[first][second]);
					break;
				}
			} else {
				//todo put in vector - it's a line
				vector<State<Problem>> rowStates;
				int row = this->_rows;
				for (int j = 0; j < this->_columns; j++) {
					State<Problem> state(make_pair(row,j),stoi(splitByComma[j]));
					rowStates.push_back(state);
				}
				this->_states.push_back(rowStates);
				rows++;
			}
			splitByComma.clear();
		}
	}

	State<Problem> getInitialState() override {
		return this->_initialState;
	}

	bool isGoalState(State<Problem> state) override {
		bool isGoal = false;
		for (auto &currentState:_goalStates) {
			//todo override ==
			if (currentState == state) {
				isGoal = true;
			}
		}
		return isGoal;
	}

	vector<State<Problem>> getAllPossibleStates() override {
		//todo this function using "in range"
		return vector<State<Problem>>();
	}


};

#endif //SEARCHPROBLEMSOLVER_MATRIX_H
