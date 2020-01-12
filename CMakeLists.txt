cmake_minimum_required(VERSION 3.15)
project(SearchProblemSolver)

set(CMAKE_CXX_STANDARD 14)

add_executable(SearchProblemSolver Solver.h Server.h MySerialServer.cpp ClientHandler.h MyTestClientHandler.h CacheManager.h FileCacheManager.h StringReverser.h)