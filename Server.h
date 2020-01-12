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
#include <thread>

void openServer(Server* server, int port, ClientHandler* clientHandler);

namespace server_side {
    class Server {
    public:
        virtual void open(int port, ClientHandler *c) = 0;

        virtual ~Server() = 0;

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

	//namespace boot{
    using namespace server_side;
	class Main{
    public:
        static int main(int argc, char *argv[]){
            Server* server = new MySerialServer();
            // arguments to MyTestClientHandler
            ClientHandler* clientHandler = new MyTestClientHandler<string,string>();
            thread serialServer(openServer, server, argv[1], clientHandler);
            serialServer.join();

            // cache test
			CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
            cacheManager->saveSolution("something", "asfdgrsfasd");
            string solution;
            if (cacheManager->hasSolution("something")) {
                solution = cacheManager->getSolution("something");
            } else {
                cout << "something" << endl;
            }
            return 0;
        }
	};
//}

void openServer(Server* server, int port, ClientHandler* clientHandler){
    server->open(port, clientHandler);
}

#endif //SEARCHPROBLEMSOLVER_SERVER_H
