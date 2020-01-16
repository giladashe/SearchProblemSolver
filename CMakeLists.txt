cmake_minimum_required(VERSION 3.15)
project(SearchProblemSolver)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(SearchProblemSolver Server.h MySerialServer.cpp ClientHandler.h MyTestClientHandler.h CacheManager.h FileCacheManager.h
        StringReverser.h main.cpp Searcher.h Searchable.h State.h SearchSolver.h BestFirstSearch.h BFS.h DFS.h AStar.h Matrix.h MyClientHandler.h)