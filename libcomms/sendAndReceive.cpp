/*
 * sendAndReceive.cpp
 *
 *  Created on: 09/06/2013
 *      Author: luisda
 */

#include "include/message_sender.hpp"
#include "include/message_receiver.hpp"
#include "include/network_interface_manager.hpp"
#include <stdexcept>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
using std::runtime_error;
using namespace std;

#define DEFAULT_DELAY_MS 			1000
#define DEFAULT_CONTINUOUS_FLAG 	false

volatile bool g_undefined_loop;

void sigsegv(int sig);
void sigusr1(int sig);
void sigusr2(int sig);
void sigint(int sig);

void show_help(void) {
	printf(" Usage: ./sendAndReceive <Net_Interface> <IP_address> <Port_number> <Message_to_send> [<Continuous(0=false, other=true)>] [<delay(ms)>]\n");
	printf("\n");
}

int main (int argc, char* argv[]) {
	int delay;
	char* ipAddr;
	char* msg;
	char* netIf;
	word port;
	word portRcv;

	g_undefined_loop = false;
	sockaddr_in* sdrInfo_p = NULL;

	printf("Número de argumentos: %i\n", argc);

	if ((argc < 5)||(argc > 7)) {
		show_help();
		exit(1);
	} else if (argc == 6) {
		delay = DEFAULT_DELAY_MS;
		g_undefined_loop = (bool)(atoi(argv[5]));
	} else if (argc == 7) {
		g_undefined_loop = (bool)(atoi(argv[5]));
		delay = atoi(argv[6]);
	} else if (argc == 5) {
		g_undefined_loop = DEFAULT_CONTINUOUS_FLAG;
		delay = DEFAULT_DELAY_MS;
	}

	netIf = argv[1];
	ipAddr = argv[2];
	port = (word)(atoi(argv[3]));
	msg = argv[4];

	signal((int)SIGSEGV, sigsegv);
	signal((int)SIGUSR1, sigusr1);
	signal((int)SIGUSR2, sigusr2);
	signal((int)SIGINT, sigint);

	do {

		CMessageSender *cMsgSdr = new CMessageSender(ipAddr, port, netIf);
		sdrInfo_p = cMsgSdr -> getSenderInformation();
		portRcv = ntohs(sdrInfo_p -> sin_port);
		printf("INFO DEL EMISOR, CON PUNTEROS: IP = %s, PORT = %d\n",
					inet_ntoa(sdrInfo_p -> sin_addr), ntohs(sdrInfo_p -> sin_port));
		cMsgSdr -> sendMessage(msg, false);
		delete cMsgSdr;

		// Antes de escuchar, debemos finalizar primero el emisor.
		CMessageReceiver *cMsgRcv = new CMessageReceiver(portRcv, netIf);
		cMsgRcv -> receiveMessage();
		delete cMsgRcv;
		usleep(1000*delay);
	} while (g_undefined_loop);

	///delete cMsgSdr;

}

void sigsegv(int sig) {
	printf ("MALO MALO... ESTO HA PEGADO UN PETARDAZO\n");
	exit(-1);
}

void sigusr1(int sig) {
	printf("Recibido SIGUSR1, cambio variable para salir del bucle \n");
	g_undefined_loop = false;
}

void sigusr2(int sig) {
	printf("RECIBIDO SIGUSR2, no hago nada\n");
}

void sigint(int sig) {
	printf("Recibido Ctrl+C, cambio variable para salir del bucle \n");
	g_undefined_loop = false;
}
