/*
 * multicast_server.hpp
 *
 *  Created on: 11/07/2012
 *      Author: luisda
 */

#ifndef MULTICAST_SERVER_HPP_
#define MULTICAST_SERVER_HPP_

#include "../../common/include/general_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_LEN 1024
#define DEFAULT_MULTICAST_TTL 1
#define DEFAULT_INTERFACE	"eth0"
#define MAX_SIZE_IF_NAME	6

class CMulticastServer {
	private:
		int m_Socket;
		unsigned char m_MulticastTTL;
		struct sockaddr_in m_MulticastAddr;
		byte* m_Buffer;
		char* m_NetInterface;
	public:
		CMulticastServer(char* multicastIP, word port, char* netInterface = NULL);
		~CMulticastServer();
		int sendMessage(char* messageToSend);

};

#endif /* MULTICAST_SERVER_HPP_ */
