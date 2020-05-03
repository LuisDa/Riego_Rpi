/*
 * message_sender.cpp
 *
 *  Created on: 12/05/2012
 *      Author: luisda
 */
//Compile with g++  -c message_sender.cpp

#include "../common/include/general_types.h"
#include "include/message_sender.hpp"


CMessageSender::CMessageSender(char* ipAddress, word port, char* netInterface) {
	m_NetInterface = NULL;
	m_NetworkIfMgr = NULL;
	m_InterfaceIP = NULL;
	m_Socket = 0;
	int sockopt = 0;
	int bindRet = 0;

	m_NetInterface = new char[MAX_SIZE_IF_NAME];
	memset(m_NetInterface, 0, sizeof(m_NetInterface));
	m_NetworkIfMgr = new CNetworkInterfaceManager();
	m_InterfaceIP = new char[MAX_IP_ADDR_SIZE];

	memset(&m_MyAddr, '\0', sizeof(m_MyAddr));
	m_MyAddr.sin_family = AF_INET;
	m_MyAddr.sin_port = 0;

	if ((m_HostEnt_p = gethostbyname(ipAddress)) == NULL) { // obtener información de máquina
		perror("SYSTEM FAILURE: gethostbyname");
		exit(1);
	}

	if ((m_Socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("SYSTEM FAILURE: socket");
		exit(1);
	}

	//if(strcmp(ipAddress, IP_LOOPBACK) != 0) {
		if (netInterface == NULL) {
			strcpy(m_NetInterface, DEFAULT_INTERFACE);
		} else {
			strcpy(m_NetInterface, netInterface);
		}

		if (sockopt = setsockopt(m_Socket, SOL_SOCKET, SO_BINDTODEVICE, m_NetInterface,
								  strlen(m_NetInterface)) < 0) {
			perror("SYSTEM FAILURE: setsockopt");
			exit(1);
		}
	//}

	if (m_NetworkIfMgr -> getInterfaceIP(m_NetInterface, m_InterfaceIP) == 0) {
		m_MyAddr.sin_addr.s_addr = inet_addr(m_InterfaceIP);
	} else {
		m_MyAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	//TODO Check if bind is necessary or not (new flag in constructor).
	// Although bind is not necessary in sender, we do it to obtain source port information
	if (bind(m_Socket, (struct sockaddr *)&m_MyAddr, sizeof(m_MyAddr)) == -1) {
		perror("WARNING: Could not obtain sender info");
	}

	int addrlen = sizeof(m_MyAddr);

	// After binding, it is necessary to obtain the port number
	if (getsockname(m_Socket, (struct sockaddr *)&m_MyAddr, (socklen_t *)&addrlen)) {
		perror("ERROR getsockname");
	}

	m_TheirAddr.sin_family = AF_INET;//If there is an error, constructor will finish with error
	// Ordenación de bytes de máquina

	m_TheirAddr.sin_port = htons(port); // short, Ordenación de bytes de la red
	m_TheirAddr.sin_addr = *((struct in_addr *)m_HostEnt_p -> h_addr);
	memset(&(m_TheirAddr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	printf("%s  %s %s %i \n", __FILE__, __FUNCTION__, ipAddress, port);
}

CMessageSender::~CMessageSender(void) {
	close(m_Socket);

	delete [] m_NetInterface;
	m_NetInterface = NULL;

	delete [] m_InterfaceIP;
	m_InterfaceIP = NULL;

	delete m_NetworkIfMgr;
	m_NetworkIfMgr = NULL;
}

int CMessageSender::sendMessage(char* msgToSend, bool confirm) {
	int numBytes = 0;

	if ((numBytes = sendto(m_Socket, msgToSend, strlen(msgToSend), 0,
		(struct sockaddr *)&m_TheirAddr, sizeof(struct sockaddr))) == -1) {
		perror("SYSTEM FAILURE: sendto");
		exit(1);
	}

	return numBytes;
}

sockaddr_in* CMessageSender::getSenderInformation(void) {
	return &m_MyAddr;
}



