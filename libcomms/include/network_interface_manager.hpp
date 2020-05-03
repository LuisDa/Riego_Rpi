/*
 * network_interface_manager.hpp
 *
 *  Created on: 04/01/2013
 *      Author: luisda
 */

#ifndef NETWORK_INTERFACE_MANAGER_HPP_
#define NETWORK_INTERFACE_MANAGER_HPP_

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

class CNetworkInterfaceManager {
	private:
		ifaddrs* m_NetworkIfList;
	public:
		CNetworkInterfaceManager(void);
		~CNetworkInterfaceManager();
		int getInterfaceIP(char* ifName, char* ipAddr);
};

#endif /* NETWORK_INTERFACE_MANAGER_HPP_ */
