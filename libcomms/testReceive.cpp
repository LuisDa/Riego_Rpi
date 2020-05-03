/*
 * testReceive.cpp
 *
 *  Created on: 27/05/2012
 *      Author: luisda
 */


#include "include/message_receiver.hpp"
#include "include/network_interface_manager.hpp"
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

void show_help(void) {
	printf(" Usage: ./testReceive <netIf> <Port_number> [<Continuous(0=false, other=true)>]\n");
	printf("\n");
}

int main (int argc, char* argv[]) {
	g_undefined_loop = false;
	CMessageReceiver *cMsgRcv;

	if (argc < 3) {
		show_help();
		exit(0);
	} else if (argc == 4) {
		g_undefined_loop = true;
	}

	sockaddr_in sdrInfo;
	sockaddr_in* sdrInfo_p = NULL;

	word port;
	char* netIf;

	netIf = argv[1];
	/*
	char* ifIP = NULL;
	ifIP = new char[NI_MAXHOST];

	//TODO Crear un Unit Test aparte para CNetworkInterfaceManager
	CNetworkInterfaceManager *cNetIfMgr = new CNetworkInterfaceManager();
	cNetIfMgr -> getInterfaceIP(netIf, ifIP);
	printf("IP Address for interface %s is %s\n", netIf, ifIP);
	delete[] ifIP;
	ifIP = NULL;
	*/
	port = (word)(atoi(argv[2]));
	signal((int)SIGSEGV, sigsegv);
	signal((int)SIGUSR1, sigusr1);
	signal((int)SIGUSR2, sigusr2);
	cMsgRcv = new CMessageReceiver(port, netIf);

	do {
		cMsgRcv -> receiveMessage();
		sdrInfo = cMsgRcv -> getSenderInfo();
		char* msg = cMsgRcv -> getReceivedMessage();
		printf("MENSAJE RECIBIDO: %s\n", msg);
		printf("HOST ORIGEN: IP = %s, PUERTO = %d \n", inet_ntoa(sdrInfo.sin_addr), ntohs(sdrInfo.sin_port));
		sdrInfo_p = cMsgRcv -> getSenderInformation();
		printf("LO MISMO, CON PUNTEROS: IP = %s, PORT = %d\n",
				inet_ntoa(sdrInfo_p -> sin_addr), ntohs(sdrInfo_p -> sin_port));
	} while(g_undefined_loop);

	printf("SOLID ROCK!!!!!!\n");
	delete cMsgRcv;
	cMsgRcv = NULL;
}

void sigsegv(int sig) {
	printf ("MALO MALO... ESTO HA PEGADO UN PETARDAZO\n");
	exit(-1);
}

void sigusr1(int sig) {
	printf("Recibido SIGUSR1 \n");
	g_undefined_loop = false;
}

void sigusr2(int sig) {
	printf("RECIBIDO SIGUSR2, no hago nada y te comes un MOHON\n");
}
