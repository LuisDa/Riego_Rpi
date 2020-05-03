/*
 * network_interface_manager.cpp
 *
 *  Created on: 05/01/2013
 *      Author: luisda
 */

#include "include/network_interface_manager.hpp"

CNetworkInterfaceManager::CNetworkInterfaceManager(void) {
	m_NetworkIfList = NULL;

    if (getifaddrs(&m_NetworkIfList) == -1) {
        perror("getifaddrs() gave an error :-(");
        exit(EXIT_FAILURE);
    }

}

CNetworkInterfaceManager::~CNetworkInterfaceManager() {
	if (m_NetworkIfList != NULL) {
		freeifaddrs(m_NetworkIfList);
	}
}

int CNetworkInterfaceManager::getInterfaceIP(char* ifName, char* ipAddr) {
	ifaddrs* ifAddrs = NULL;
	int family = 0;
	int resGetNameInfo = 0;

	for (ifAddrs = m_NetworkIfList; ifAddrs != NULL; ifAddrs = ifAddrs->ifa_next) {
		if (ifAddrs->ifa_addr == NULL) {
			continue;
		}

		family = ifAddrs->ifa_addr->sa_family;

		if (family == AF_INET) {
			resGetNameInfo = getnameinfo(ifAddrs->ifa_addr,
										 sizeof(struct sockaddr_in),
                                         ipAddr,
                                         NI_MAXHOST,
                                         NULL,
                                         0,
                                         NI_NUMERICHOST);

            if (resGetNameInfo != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(resGetNameInfo));
                exit(EXIT_FAILURE);
            } else if (strcmp(ifName, ifAddrs->ifa_name) == 0) {
    			return EXIT_SUCCESS;
    		}
		}
	}

	printf("ERROR: No such interface: %s\n", ifName);
	memset(ipAddr, 0, NI_MAXHOST);
	return EXIT_FAILURE;
}
