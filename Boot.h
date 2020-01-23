#ifndef SEARCHPROBLEMSOLVER_BOOT_H
#define SEARCHPROBLEMSOLVER_BOOT_H

#include <iostream>
#include "FileCacheManager.h"
#include "StringReverser.h"
#include "Matrix.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "AStar.h"
#include "ClientHandler.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "Server.h"
#include <thread>
#include "Solver.h"
#include "StringReverser.h"
#include "SearchSolver.h"
#include "MyClientHandler.h"
#include <netinet/in.h>
#include <algorithm>
#include <arpa/inet.h>
#include <unistd.h>

using namespace server_side;
using namespace std;

void openServer(Server *server, int port, ClientHandler *clientHandler);


namespace boot {
	class Main;
}
class boot::Main {
public:
	Main() = default;

	~Main() = default;

	static void main(int argc, char *argv[]) {

		Searcher<string, string> *searcher = new AStar<string, string>();
		Solver<string, string> *solver = new SearchSolver<string, string>(searcher);
		Server *server = new MyParallelServer();
		CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
		// arguments to MyTestClientHandler
		ClientHandler *clientHandler = new MyClientHandler<string, string>(solver, cacheManager);
		int serverPort;
		//put port 5600 if doesn't have
		if (argc > 1) {
			serverPort = stoi(argv[1]);
		} else {
			serverPort = 5600;
		}
		//make thread for the server (parallel/serial)
		thread parallelServer(openServer, server, serverPort, clientHandler);
		parallelServer.join();
	}


};

void openServer(Server *server, int port, ClientHandler *clientHandler) {
	server->open(port, clientHandler);
	delete server;
}

#endif //SEARCHPROBLEMSOLVER_BOOT_H
