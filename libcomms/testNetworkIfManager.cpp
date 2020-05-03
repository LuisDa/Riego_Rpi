/*
 * testNetworkIfManager.cpp
 *
 *  Created on: 07/01/2013
 *      Author: luisda
 */
#include <stdexcept>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "include/network_interface_manager.hpp"

void show_usage(void) {
	printf("Usage: ./testNetworkIfManager <interface_name>\n");
	printf(" (<interface_name> can be eth0, wlan0, lo, eth1, etcetera)\n");
	printf(" For additional info about available interfaces, execute ifconfig\n");
}

int main(int argc, char* argv[]) {
	char* ifName = NULL;

	if (argc < 2) {
		show_usage();
		exit(1);
	} else {
		ifName = argv[1];
	}

	char* ipAddress = NULL;
	CNetworkInterfaceManager *cNetIfMgr = new CNetworkInterfaceManager();
	ipAddress = new char[NI_MAXHOST];
	int result = cNetIfMgr -> getInterfaceIP(ifName, ipAddress);
	if (result == 0) {
		printf("For interface %s, IP Address is %s\n", ifName, ipAddress);
	}

	delete[] ipAddress;
	ipAddress = NULL;
	delete cNetIfMgr;
	cNetIfMgr = NULL;
	exit(result);
}
