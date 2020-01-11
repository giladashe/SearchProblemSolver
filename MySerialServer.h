//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_MYSERIALSERVER_H
#define SEARCHPROBLEMSOLVER_MYSERIALSERVER_H


#include "Server.h"
#include "ClientHandler.h"
using namespace server_side;
class MySerialServer: public Server {

	bool _stop = false;
public:
	~MySerialServer() override;

	// pure virtual execute so the other commands classes will have to implement
	void stop() override;

	void open(int port, ClientHandler* c) override ;
};

#endif //SEARCHPROBLEMSOLVER_MYSERIALSERVER_H
