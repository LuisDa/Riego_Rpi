/*
 * message_receiver.cpp
 *
 *  Created on: 27/05/2012
 *      Author: luisda
 *
 *  Clase que define un receptor de mensajes IP utilizando UDP.
 */

#include "../common/include/general_types.h"
#include "include/message_receiver.hpp"

CMessageReceiver::CMessageReceiver(word port, char* netInterface) {
	m_Socket = 0;
	int sockopt = 0;
	m_NetInterface = new char[MAX_SIZE_IF_NAME];
	m_InterfaceIP = new char[MAX_IP_ADDR_SIZE];
	m_NetworkIfMgr = new CNetworkInterfaceManager();

	if ((m_Socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("SYSTEM FAILURE: socket");
		exit(1);
	}

	m_MyAddr.sin_family = AF_INET;

	// Ordenación de bytes de máquina
	m_MyAddr.sin_port = htons(port);

	if (netInterface == NULL) {
		strcpy(m_NetInterface, DEFAULT_INTERFACE);
	} else {
		strcpy(m_NetInterface, netInterface);
	}
	/*
	//FIXME: No filtra bien el interfaz. Quizás sea mejor leer la IP del mismo para escuchar...
	if (sockopt = setsockopt(m_Socket, SOL_SOCKET, SO_BINDTODEVICE, m_NetInterface,
		strlen(m_NetInterface)) < 0) {
		perror("SYSTEM FAILURE: setsockopt");
		exit(1);
	}
	*/
	//TODO: Leer la interfaz pasada como parámetro y obtener su IP.
	//TODO: contemplar también el caso de loopback.
	// short, Ordenación de bytes de la red
	if (m_NetworkIfMgr -> getInterfaceIP(m_NetInterface, m_InterfaceIP) == 0) {
		m_MyAddr.sin_addr.s_addr = inet_addr(m_InterfaceIP);
	} else {
		m_MyAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	//m_MyAddr.sin_addr.s_addr = htonl(INADDR_ANY); // rellenar con mi dirección IP
	//m_MyAddr.sin_addr.s_addr = inet_addr("192.168.1.41"); //TODO rellenar con mi dirección IP
	memset(&(m_MyAddr.sin_zero), '\0', 8); // poner a cero el resto de la estructura

	if (bind(m_Socket, (struct sockaddr *)&m_MyAddr, sizeof(struct sockaddr)) == -1) {
		close(m_Socket);
		perror("SYSTEM FAILURE: bind");
		exit(1);
	}

	m_Buffer = new char[MAXBUFLEN];
}

CMessageReceiver::~CMessageReceiver(void) {
	delete[] m_Buffer;
	m_Buffer = NULL;

	delete[] m_NetInterface;
	m_NetInterface = NULL;

	delete[] m_InterfaceIP;
	m_InterfaceIP = NULL;

	delete m_NetworkIfMgr;
	m_NetworkIfMgr = NULL;

	close(m_Socket);
}

int CMessageReceiver::receiveMessage(bool receive) {
	int numBytes = 0;
	
	if (receive)
	{
	#ifndef	__cplusplus
		int addr_len = sizeof(struct sockaddr_in); //With C++ it does NOT compile.
	#else
		socklen_t addr_len = sizeof(struct sockaddr_in);
	#endif
	
	/*
		if ((numBytes=recvfrom(m_Socket, m_Buffer, MAXBUFLEN-1, 0,
			(struct sockaddr *)&m_TheirAddr, &addr_len)) == -1) {
			perror("SYSTEM FAILURE: recvfrom");
			exit(1);
		}
		*/
		
		if ((numBytes=recvfrom(m_Socket, m_Buffer, MAXBUFLEN-1, EAGAIN,
			(struct sockaddr *)&m_TheirAddr, &addr_len)) == -1) {
			perror("SYSTEM FAILURE: recvfrom");
			//exit(1);
		}
					

		printf("- Got packet from %s\n", inet_ntoa(m_TheirAddr.sin_addr));
		printf("- Packet is %d bytes long\n", numBytes);
		m_Buffer[numBytes] = '\0';
		printf("- packet contains \"%s\"\n", m_Buffer);
	}

	return numBytes;
}

char* CMessageReceiver::getReceivedMessage(void) {
	return m_Buffer;
}

sockaddr_in CMessageReceiver::getSenderInfo(void) {
	return m_TheirAddr;
}

sockaddr_in* CMessageReceiver::getSenderInformation(void) {
	return &m_TheirAddr;
}
