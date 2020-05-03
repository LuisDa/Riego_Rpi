/*
 * message_sender.hpp
 *
 *  Created on: 13/05/2012
 *      Author: luisda
 */

#ifndef MESSAGE_SENDER_H_
#define MESSAGE_SENDER_H_

#define DEFAULT_INTERFACE	"eth0"
#define MAX_SIZE_IF_NAME	6
#define IP_LOOPBACK 		"127.0.0.1"
#define MAX_IP_ADDR_SIZE	NI_MAXHOST

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

class CMessageSender {
	private:
		int m_Socket;
		sockaddr_in m_TheirAddr;
		sockaddr_in m_MyAddr;
		hostent *m_HostEnt_p;
		char* m_NetInterface;
		char* m_InterfaceIP;
		CNetworkInterfaceManager* m_NetworkIfMgr;

	public:
		CMessageSender(char* ipAddress, word port, char* netInterface = NULL);
		~CMessageSender();
		int sendMessage(char* msgToSend, bool confirm);
		sockaddr_in* getSenderInformation(void);


};

#endif /* MESSAGE_SENDER_H_ */
