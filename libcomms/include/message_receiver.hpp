/*
 * message_receiver.hpp
 *
 *  Created on: 23/05/2012
 *      Author: luisda
 *
 *  Clase que define un receptor de mensajes IP utilizando UDP.
 */

#ifndef MESSAGE_RECEIVER_H_
#define MESSAGE_RECEIVER_H_

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
#include <ifaddrs.h>

#define MAXBUFLEN 100
#define DEFAULT_INTERFACE    "eth0"
#define MAX_SIZE_IF_NAME    6
#define IP_LOOPBACK         "127.0.0.1"
#define MAX_IP_ADDR_SIZE	NI_MAXHOST

class CMessageReceiver {
	private:
		char* m_Buffer;
		sockaddr_in m_MyAddr;
		sockaddr_in m_TheirAddr;
		int m_Socket;
		char* m_NetInterface;
		char* m_InterfaceIP;
		CNetworkInterfaceManager* m_NetworkIfMgr;
	public:
		CMessageReceiver(word port, char* netInterface);
		~CMessageReceiver();
		int receiveMessage(bool receive=true); //Si le pasamos true, recibir (por si la incluimos en una hebra), si false, saltarse la función
		char* getReceivedMessage(void);
		sockaddr_in getSenderInfo (void);
		sockaddr_in* getSenderInformation(void);

};

#endif /* MESSAGE_RECEIVER_H_ */
