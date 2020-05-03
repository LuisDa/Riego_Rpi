/*
 * multicast_server.cpp
 *
 *  Created on: 15/07/2012
 *      Author: luisda
 */

#include "../common/include/general_types.h"
#include "include/multicast_server.hpp"

CMulticastServer::CMulticastServer(char* multicastIP, word port, char* netInterface) {
	m_Socket = 0;
	m_Buffer = NULL;
	m_MulticastTTL = DEFAULT_MULTICAST_TTL;
	m_NetInterface = NULL;

	m_NetInterface = new char[MAX_SIZE_IF_NAME];
	memset(m_NetInterface, 0, sizeof(m_NetInterface));

	// Crear socket de datagramas, especificando el protocolo de transporte UDP
	if ((m_Socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		perror("ERROR: Socket creation failed");
		exit(1);
	}

	if (netInterface == NULL) {
		strcpy(m_NetInterface, DEFAULT_INTERFACE);
	} else {
		strcpy(m_NetInterface, netInterface);
	}

	// En primer lugar especificamos, en el socket, el interfaz de red sobre el que enviar los datagramas.
	if ((setsockopt(m_Socket, SOL_SOCKET, SO_BINDTODEVICE, m_NetInterface, strlen(m_NetInterface))) < 0) {
		perror("ERROR: setsockopt() failed when specifying options to select network interface");
		exit(1);
	}

	// Posteriormente especificamos, en el socket, opciones para Multicast.
	if ((setsockopt(m_Socket, IPPROTO_IP, IP_MULTICAST_TTL, (void*) &m_MulticastTTL, sizeof(m_MulticastTTL))) < 0)
	{
		perror("ERROR: setsockopt() failed");
		exit(1);
	}

	memset(&m_MulticastAddr, 0, sizeof(m_MulticastAddr));
	m_MulticastAddr.sin_family      = AF_INET;
	m_MulticastAddr.sin_addr.s_addr = inet_addr(multicastIP);
	m_MulticastAddr.sin_port        = htons(port);
	m_Buffer = new byte[MAX_LEN];
	memset(m_Buffer, 0, sizeof(m_Buffer)*sizeof(byte));
}

CMulticastServer::~CMulticastServer() {
	delete[] m_Buffer;
	m_Buffer = NULL;

	delete[] m_NetInterface;
	m_NetInterface = NULL;

	close(m_Socket);
}

int CMulticastServer::sendMessage(char* messageToSend) {
	int numBytes = 0;
	int send_len = strlen(messageToSend);
	memcpy(m_Buffer, messageToSend, send_len);
	m_Buffer[send_len] = '\0';

	if ((numBytes = sendto(m_Socket, m_Buffer, send_len, 0,
	(struct sockaddr *) &m_MulticastAddr,
	sizeof(m_MulticastAddr))) != send_len)
	{
		perror("ERROR: sendto() failed");
		exit(1);
	}

	return numBytes;
}
