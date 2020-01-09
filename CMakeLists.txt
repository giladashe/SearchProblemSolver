cmake_minimum_required(VERSION 3.15)
project(SearchProblemSolver)

set(CMAKE_CXX_STANDARD 14)

add_executable(SearchProblemSolver main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h CacheManager.h FileCacheManager.cpp FileCacheManager.h Solver.h)