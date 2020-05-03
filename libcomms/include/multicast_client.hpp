/*
 * multicast_client.hpp
 *
 *  Created on: 23/07/2012
 *      Author: luisda
 */

#ifndef MULTICAST_CLIENT_HPP_
#define MULTICAST_CLIENT_HPP_

#include "../../common/include/general_types.h"
#include "network_interface_manager.hpp"
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
#define DEFAULT_INTERFACE    "eth0"
#define MAX_SIZE_IF_NAME    6
#define MAX_IP_ADDR_SIZE	NI_MAXHOST

class CMulticastClient {
	private:
		int m_Socket;
		int m_FlagOn; //Can be 1 or 0
		sockaddr_in m_MulticastAddr;
		char* m_MessageReceived;
		int m_MsgrecvLen;
		ip_mreq m_MulticastReq; //Multicast Request to join group
		sockaddr_in m_ServerAddr; //Server TCP/IP information
		CNetworkInterfaceManager* m_NetworkIfMgr;
		char* m_NetInterface;
		char* m_InterfaceIP;

	public:
		CMulticastClient(void);
		~CMulticastClient();
		void joinToMulticastGroup(char* multicastIP, word multicastPort, char* netInterface);
		void receive(void);
		void dropFromMulticastGroup(void);
		char* getReceivedMessage(void);
		sockaddr_in getSenderInfo (void);
		sockaddr_in* getSenderInformation(void);
};

#endif /* MULTICAST_CLIENT_HPP_ */
