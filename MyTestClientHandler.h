

#ifndef SEARCHPROBLEMSOLVER_MYTESTCLIENTHANDLER_H
#define SEARCHPROBLEMSOLVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <algorithm>
#include <arpa/inet.h>


template<class Problem, class Solution>
class MyTestClientHandler: public ClientHandler {
    Solver<Problem, Solution>* _solver;
    CacheManager<Problem, Solution> *_cm;
public:
    MyTestClientHandler(Solver<Problem, Solution>* solver, CacheManager<Problem, Solution> *cm) {
        this->_solver = solver;
        this->_cm = cm;
    }

    virtual void handleClient(int clientSocket) {
        // initialize buffer to 0
        char buffer[1024] = {0};
        string between_lines;

        // read
        int readData = read(clientSocket, buffer, 1024);
        int i = 0;
        while (i < readData) {
            if (between_lines == "end"){
                close(clientSocket);
            }
            if (i == 6) {
                if (this->_cm->hasSolution(between_lines)) {
                    int is_sent = send(clientSocket, this->_cm->getSolution(between_lines).c_str(),
                                       this->_cm->getSolution(between_lines).length(), 0);
                    if (is_sent == -1) {
                        cout << "Error sending message" << endl;
                    }
                }
                else{
                    Solution solution = this->_solver->solve(between_lines);
                    this->_cm->saveSolution(between_lines, solution);
                    int is_sent = send(clientSocket, this->_cm->getSolution(between_lines).c_str(),
                                       this->_cm->getSolution(between_lines).length(), 0);
                    if (is_sent == -1) {
                        cout << "Error sending message" << endl;
                    }
                }
                between_lines = "";
                i++;
                continue;
            }
            between_lines += buffer[i];
            i++;
        }
    }

                /*vector<string> splittedByCom = Lexer::splitByDelimiter(between_lines, ",");
                // updating the maps
                int k;
                for (k = 0; k < (int) splittedByCom.size(); k++) {
                    //update the key in simMap
                    string s = splittedByCom[k];
                    if (!s.empty()) {
                        data->setValueSimMap(xmlVariables[k], stod(s));
                        //if there is a bind between the maps it updates the value of the varData in progMap
                        if ((data->getBindFromSimMap(xmlVariables[k]) == 1)) {
                            data->setValueProgMap(data->getProgFromSimMap(xmlVariables[k]), (stod(s)));
                        }//
                    }
                }
                between_lines = "";
                i++;
                continue;
            }
            between_lines+= buffer[i];
            i++;*/


};

#endif //SEARCHPROBLEMSOLVER_MYTESTCLIENTHANDLER_H
