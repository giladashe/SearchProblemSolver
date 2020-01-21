//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SERVER_H
#define SEARCHPROBLEMSOLVER_SERVER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "Server.h"


namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *c) = 0;

        virtual ~Server(){}

    };
    class MySerialServer: public Server {
    public:
        ~MySerialServer() override;

        void open(int port, ClientHandler* c) override ;
    };

	class MyParallelServer: public Server {
	public:
		~MyParallelServer() override;

		void open(int port, ClientHandler* c) override ;
	};

}

#endif //SEARCHPROBLEMSOLVER_SERVER_H
