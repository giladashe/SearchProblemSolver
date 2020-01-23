#ifndef SEARCHPROBLEMSOLVER_MYCLIENTHANDLER_H
#define SEARCHPROBLEMSOLVER_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <algorithm>
#include <arpa/inet.h>


template<class Problem, class Solution>
class MyClientHandler : public ClientHandler {
	Solver<Problem, Solution> *_solver;
	CacheManager<Problem, Solution> *_cm;
public:
	MyClientHandler(Solver<Problem, Solution> *solver, CacheManager<Problem, Solution> *cm) {
		this->_solver = solver;
		this->_cm = cm;
	}


	void handleClient(int clientSocket) override {
		bool stop = false;
		string between_lines;
		string allMatrix; // with start & end points

		while (!stop) {
			// initialize buffer to 0
			char buffer[2048] = {0};
			// read
			int readData = read(clientSocket, buffer, 2048);
			int i = 0;
			while (i < readData) {
				if (between_lines == "end") {
					stop = true;
					Solution solution;
					if (!this->_cm->hasSolution(allMatrix)) {
						solution = this->_solver->solve(allMatrix);
						this->_cm->saveSolution(allMatrix, solution);
					} else {
						solution = this->_cm->getSolution(allMatrix);
					}
					int is_sent = send(clientSocket, solution.c_str(),
									   solution.length(), 0);
					if (is_sent == -1) {
						cout << "Error sending message" << endl;
					}
					close(clientSocket);
					break;
				}
				if (buffer[i] == '\n') {
					allMatrix.append(between_lines);
					allMatrix.append("\n");
					between_lines = "";
					i++;
					continue;
				}
				between_lines += buffer[i];
				i++;
			}
		}
	}

	ClientHandler *clone() override {
		return new MyClientHandler<Problem, Solution>(_solver->clone(), _cm->clone());
	}

	~MyClientHandler() override {
		delete this->_cm;
		delete this->_solver;
	}
};

#endif //SEARCHPROBLEMSOLVER_MYCLIENTHANDLER_H
