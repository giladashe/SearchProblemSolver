cmake_minimum_required(VERSION 3.15)
project(SearchProblemSolver)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(SearchProblemSolver Server.h MySerialServer.cpp ClientHandler.h MyTestClientHandler.h CacheManager.h FileCacheManager.h
        StringReverser.h Main.cpp)