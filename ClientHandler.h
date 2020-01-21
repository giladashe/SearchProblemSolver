

#ifndef SEARCHPROBLEMSOLVER_CLIENTHANDLER_H
#define SEARCHPROBLEMSOLVER_CLIENTHANDLER_H

#include <iostream>

using namespace std;

class ClientHandler {
public:
	virtual void handleClient(int clientSocket) = 0;

	virtual ClientHandler *clone() = 0;

};


#endif //SEARCHPROBLEMSOLVER_CLIENTHANDLER_H
