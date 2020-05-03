/*
 * multicast_client.cpp
 *
 *  Created on: 20/08/2012
 *      Author: luisda
 */

#include "include/multicast_client.hpp"

CMulticastClient::CMulticastClient(void) {
	m_Socket = 0;
	m_FlagOn = 1;
	m_MessageReceived = NULL;
	m_MsgrecvLen = 0;
	memset(&m_MulticastAddr, 0, sizeof(m_MulticastAddr));
	memset(&m_MulticastReq, 0, sizeof(m_MulticastReq));
	memset(&m_ServerAddr, 0, sizeof(m_ServerAddr));
	m_MessageReceived = new char[MAX_LEN];
	memset(m_MessageReceived, 0, MAX_LEN);
	m_NetworkIfMgr = new CNetworkInterfaceManager();
	m_NetInterface = new char[MAX_SIZE_IF_NAME];
	m_InterfaceIP = new char[MAX_IP_ADDR_SIZE];

	if ((m_Socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		perror("ERROR: socket() failed");
		exit(1);
	}

	if ((setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, &m_FlagOn,
		sizeof(m_FlagOn))) < 0)
	{
		perror("ERROR: setsockopt() failed");
		exit(1);
	}
}

CMulticastClient::~CMulticastClient(void) {
	delete[] m_MessageReceived;
	m_MessageReceived = NULL;

	delete[] m_NetInterface;
	m_NetInterface = NULL;

	delete[] m_InterfaceIP;
	m_InterfaceIP = NULL;

	delete m_NetworkIfMgr;
	m_NetworkIfMgr = NULL;

	close(m_Socket);
}

void CMulticastClient::joinToMulticastGroup (char* multicastIP, word multicastPort, char* netInterface) {
	if (netInterface == NULL) {
		strcpy(m_NetInterface, DEFAULT_INTERFACE);
	} else {
		strcpy(m_NetInterface, netInterface);
	}

	m_MulticastAddr.sin_family      = AF_INET;
	m_MulticastAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_MulticastAddr.sin_port        = htons(multicastPort);

	if ((bind(m_Socket, (struct sockaddr *) &m_MulticastAddr, sizeof(m_MulticastAddr))) < 0)
	{
		perror("ERROR: bind() failed");
		exit(1);
	}

	/* construct an IGMP join request structure */
	m_MulticastReq.imr_multiaddr.s_addr = inet_addr(multicastIP);

	if (m_NetworkIfMgr -> getInterfaceIP(m_NetInterface, m_InterfaceIP) == 0) {
		m_MulticastReq.imr_interface.s_addr = inet_addr(m_InterfaceIP);
	} else {
		m_MulticastReq.imr_interface.s_addr = htonl(INADDR_ANY);
	}

	if ((setsockopt(m_Socket, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		(void*) &m_MulticastReq, sizeof(m_MulticastReq))) < 0)
	{
		perror("ERROR: setsockopt() failed when joining to Multicast group");
		exit(1);
	}
}

void CMulticastClient::receive(void) {
#ifndef __cplusplus
	int from_len = sizeof(m_ServerAddr);
#else
	socklen_t from_len = sizeof(struct sockaddr_in);
#endif
	memset(m_MessageReceived, 0, MAX_LEN);
	memset(&m_ServerAddr, 0, from_len);

	/* block waiting to receive a packet */
	if ((m_MsgrecvLen = recvfrom(m_Socket, m_MessageReceived, MAX_LEN,
		 0, (struct sockaddr*)&m_ServerAddr, &from_len)) < 0)
	{
		perror("ERROR: recvfrom() failed");
	}

	m_MessageReceived[m_MsgrecvLen] = '\0';
}

void CMulticastClient::dropFromMulticastGroup(void) {
	if ((setsockopt(m_Socket, IPPROTO_IP, IP_DROP_MEMBERSHIP,
		(void*) &m_MulticastReq, sizeof(m_MulticastReq))) < 0)
	{
		perror("ERROR: setsockopt() failed");
		exit(1);
	} else {
		printf("Finishing...\n");
	}
}

char* CMulticastClient::getReceivedMessage(void) {
	return m_MessageReceived;
}

sockaddr_in CMulticastClient::getSenderInfo(void) {
	return m_ServerAddr;
}

sockaddr_in* CMulticastClient::getSenderInformation(void) {
	return &m_ServerAddr;
}
