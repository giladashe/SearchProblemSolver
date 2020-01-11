//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SERVER_H
#define SEARCHPROBLEMSOLVER_SERVER_H

#include "ClientHandler.h"
#include "MySerialServer.h"

namespace server_side {
	class Server {
	public:
		virtual void open(int port, ClientHandler* c) = 0;

		virtual ~Server() = 0;

		virtual void stop() = 0;
	};
}
namespace boot{
	class Main{
	public:
		static int main(int argc, char *argv[]){
			server_side::Server* server = new MySerialServer();
			CacheManager<string,string> *cacheManager = new FileCacheManager<string,string>();
            cacheManager->saveSolution("something", "asfdgrsfasd");
            string solution;
            if (cacheManager->hasSolution("something")) {
                solution = cacheManager->getSolution("something");
            } else {
                cout << "something" << endl;
            }


        }
	};
}


#endif //SEARCHPROBLEMSOLVER_SERVER_H
