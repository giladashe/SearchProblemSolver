//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_CLIENTHANDLER_H
#define SEARCHPROBLEMSOLVER_CLIENTHANDLER_H

#include <iostream>
using namespace std;
class ClientHandler {
public:
	//ints for sockets
	virtual void handleClient(int inputStream, int outputStream)=0;
};


#endif //SEARCHPROBLEMSOLVER_CLIENTHANDLER_H
