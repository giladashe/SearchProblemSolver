//
// Created by giladasher on 08/01/2020.
//

#include "Server.h"
#include <netinet/in.h>
#include <iostream>
#include <thread>


using namespace server_side;

void getFromClient(int client_socket, ClientHandler *clientHandler);

MyParallelServer::~MyParallelServer() {

}

void MyParallelServer::stop() {
	this->_stop = true;
}

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
	int socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1) {
		//error
		cerr << "Could not create a socket" << endl;
		exit(1);
	}

	//bind socket to IP address -  we first need to create the sockaddr obj.
	sockaddr_in address{}; //in means IP4
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
	address.sin_port = htons(port); //we need to convert our number to a number that the network understands.

	//the actual bind command
	if (bind(socketFd, (struct sockaddr *) &address, sizeof(address)) == -1) {
		cerr << "Could not bind the socket to an IP" << endl;
		exit(1);
	}

	//making socket listen to the port
	if (listen(socketFd, 5) == -1) { //can also set to SOMAXCON (max connections)
		cerr << "Error during listening command" << endl;
		exit(1);
	} else {
		cout << "Server is now listening ..." << endl;
	}

	while (!_stop) {
		// accepting a client
		struct timeval tv{};
		tv.tv_sec = 120;
		setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);
		int client_socket = accept(socketFd, (struct sockaddr *) &address,
								   (socklen_t *) &address);
		if (client_socket == -1) {
			cerr << "Error accepting client" << endl;
			exit(1);
		}
		// connect to server
		int is_connect = 0;
		is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
		if (is_connect == -1) {
			cerr << "Could not connect" << endl;
			exit(1);
		}
		cout << "Client is now connected to server" << endl;
		//thread acceptClient(getFromClient, client_socket, clientHandler);
		//acceptClient.detach();
		getFromClient(client_socket,clientHandler);

	}
}

void getFromClient(int client_socket, ClientHandler *clientHandler) {

	clientHandler->handleClient(client_socket);
}
