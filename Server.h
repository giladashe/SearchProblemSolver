//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SERVER_H
#define SEARCHPROBLEMSOLVER_SERVER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "Server.h"


namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *c) = 0;

        virtual ~Server(){}

        virtual void stop() = 0;

    };
    class MySerialServer: public Server {
        bool _stop = false;
    public:
        ~MySerialServer() override;

        // pure virtual execute so the other commands classes will have to implement
        void stop() override;

        void open(int port, ClientHandler* c) override ;
    };

}

#endif //SEARCHPROBLEMSOLVER_SERVER_H
