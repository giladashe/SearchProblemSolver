//
// Created by giladasher on 08/01/2020.
//

#ifndef SEARCHPROBLEMSOLVER_SERVER_H
#define SEARCHPROBLEMSOLVER_SERVER_H

#include "ClientHandler.h"

namespace server_side {
	class Server {
	public:
		virtual void open(int port, ClientHandler c) = 0;

		virtual ~Server() = 0;

		virtual void stop() = 0;
	};
}


#endif //SEARCHPROBLEMSOLVER_SERVER_H
