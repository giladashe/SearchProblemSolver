//
// Created by shaiyis on 1/13/20.
//

#include "ClientHandler.h"
#include "CacheManager.h"
#include "MySerialServer.h"
#include "FileCacheManager.h"
#include "MyTestClientHandler.h"
#include "Server.h"
#include <thread>
#include "Solver.h"
#include "StringReverser.h"
#include <netinet/in.h>
#include <algorithm>
#include <arpa/inet.h>
#include <unistd.h>


using namespace server_side;
void openServer(Server* server, int port, ClientHandler* clientHandler);


/*namespace boot{
    using namespace server_side;
    class Main{
    public:
        static int main(int argc, char *argv[]){
            Server* server = new MySerialServer();
            Solver* solver = new StringReverser<string, string>();
            CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
            // arguments to MyTestClientHandler
            ClientHandler* clientHandler = new MyTestClientHandler<string,string>(solver, cacheManager);
            thread serialServer(openServer, server, argv[1], clientHandler);
            serialServer.join();

            // cache test
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
}*/


int main(int argc, char *argv[]){
    Solver<string, string>* solver = new StringReverser<string, string>();
    Server* server = new MySerialServer();
    CacheManager<string, string> *cacheManager = new FileCacheManager<string, string>();
    // arguments to MyTestClientHandler
    ClientHandler* clientHandler = new MyTestClientHandler<string,string>(solver, cacheManager);
    thread serialServer(openServer, server, stoi(argv[1]), clientHandler);
    serialServer.join();

    return 0;
}
/*using namespace boot;
int main(){
    boot::Main* main = new Main();
    main->main(int argc, char *argv[]);*/


void openServer(Server* server, int port, ClientHandler* clientHandler){
    server->open(port, clientHandler);
}
