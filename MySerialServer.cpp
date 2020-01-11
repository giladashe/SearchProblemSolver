//
// Created by giladasher on 08/01/2020.
//

#include "MySerialServer.h"

MySerialServer::~MySerialServer() {
}

void MySerialServer::stop() {
    this->_stop = true;
}

void MySerialServer::open(int port, ClientHandler* c){
    while (!_stop){

    }
}
