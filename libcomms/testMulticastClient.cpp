/*
 * testMulticastClient.cpp
 *
 *  Created on: 21/08/2012
 *      Author: luisda
 */
#include "include/multicast_client.hpp"
#include <stdexcept>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
using std::runtime_error;
using namespace std;

bool g_undefined_loop;

void sigsegv(int sig);
void sigusr1(int sig);
void sigusr2(int sig);

#define DEFAULT_DELAY_MS 			1000
#define DEFAULT_CONTINUOUS_FLAG 	false

void show_help(void) {
	printf(" Usage: ./testMulticastClient <net_Interface> <IP_address> <Port_number>\n");
	printf("\n");
}

int main (int argc, char* argv[]) {
	char* ipAddr;
	char* msg;
	char* netIf;
	word port;

	if (argc < 4) {
		show_help();
		exit(0);
	} else if (argc == 5) {
		g_undefined_loop = true;
	}

	netIf = argv[1];
	ipAddr = argv[2];
	port = (word)(atoi(argv[3]));
	sockaddr_in* sdrInfo_p = NULL;

	signal((int)SIGSEGV, sigsegv);
	signal((int)SIGUSR1, sigusr1);
	signal((int)SIGUSR2, sigusr2);

	CMulticastClient *cMtcClt = new CMulticastClient;
	cMtcClt -> joinToMulticastGroup(ipAddr, port, netIf);

	do {
		cMtcClt -> receive();
		sdrInfo_p = cMtcClt -> getSenderInformation();
		msg = cMtcClt ->getReceivedMessage();
		printf("MENSAJE RECIBIDO: %s\n", msg);
		printf("HOST ORIGEN: IP = %s, PORT = %d\n",
						inet_ntoa(sdrInfo_p -> sin_addr), ntohs(sdrInfo_p -> sin_port));

	} while (g_undefined_loop);

	cMtcClt -> dropFromMulticastGroup();
	delete cMtcClt;
}

void sigsegv(int sig) {
	printf ("FATALITY!!!!!!!!  ");
	printf("CÓMETE UN MOJÓN \n");
	exit(-1);
}

void sigusr1(int sig) {
	printf("Recibido SIGUSR1 \n");
	g_undefined_loop = false;
}

void sigusr2(int sig) {
	printf("RECIBIDO SIGUSR2, no hago nada y te comes un MOHON\n");
}

