//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_MYTESTCLIENTHANDLER_H
#define SEARCHPROBLEMSOLVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"

template<class Problem, class Solution>
class MyTestClientHandler: public ClientHandler{
Solver<Problem,Solution> _solver;
CacheManager _cm;
public:
	MyTestClientHandler(Solver<Problem,Solution> solver, CacheManager cm);
};

#endif //SEARCHPROBLEMSOLVER_MYTESTCLIENTHANDLER_H
