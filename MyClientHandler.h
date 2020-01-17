//
// Created by shaiyis on 1/15/20.
//

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
class MyClientHandler: public ClientHandler {
    Solver<Problem, Solution>* _solver;
    CacheManager<Problem, Solution> *_cm;
public:
    MyClientHandler(Solver<Problem, Solution>* solver, CacheManager<Problem, Solution> *cm) {
        this->_solver = solver;
        this->_cm = cm;
    }
//
    virtual void handleClient(int clientSocket) {
        bool stop = false;
        string between_lines;
        string allMatrix; // with start & end points

        while (!stop){
            // initialize buffer to 0
            char buffer[1024] = {0};
            // read
            int readData = read(clientSocket, buffer, 1024);
            int i = 0;
            while (i < readData) {
                if (between_lines == "end"){
                    stop = true;
                    if (this->_cm->hasSolution(allMatrix)) {
                        int is_sent = send(clientSocket, this->_cm->getSolution(allMatrix).c_str(),
                                           this->_cm->getSolution(allMatrix).length(), 0);
                        if (is_sent == -1) {
                            cout << "Error sending message" << endl;
                        }
                    }
                    else{
                        Solution solution = this->_solver->solve(allMatrix);
                        this->_cm->saveSolution(allMatrix, solution);
                        int is_sent = send(clientSocket, this->_cm->getSolution(allMatrix).c_str(),
                                           this->_cm->getSolution(allMatrix).length(), 0);
                        if (is_sent == -1) {
                            cout << "Error sending message" << endl;
                        }
                    }
                    close(clientSocket);
                }
                if (buffer[i] == '\n'){
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
};


#endif //SEARCHPROBLEMSOLVER_MYCLIENTHANDLER_H
