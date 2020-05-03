/*
 * receiveAndReply.cpp
 *
 *  Created on: 24/08/2013
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

void show_help(void) {
	printf(" Usage: ./receiveAndReply <Net_Interface> <Port_number> <Reply_message> [<Continuous(0=false, other=true)>] [<delay(ms)>]\n");
	printf("\n");
}

int main (int argc, char* argv[]) {
	int delay;
	char* ipAddr;
	char* msg;
	char* netIf;
	word port;
	word portSdr;

	g_undefined_loop = false;
	sockaddr_in* sdrInfo_p = NULL;

	if ((argc < 4)||(argc > 6)) {
		show_help();
		exit(1);
	} else if (argc == 5) {
		delay = DEFAULT_DELAY_MS;
		g_undefined_loop = (bool)(atoi(argv[4]));
	} else if (argc == 6) {
		g_undefined_loop = (bool)(atoi(argv[4]));
		delay = atoi(argv[5]);
	} else if (argc == 4) {
		g_undefined_loop = DEFAULT_CONTINUOUS_FLAG;
		delay = DEFAULT_DELAY_MS;
	}

	netIf = argv[1];
	port = (word)(atoi(argv[2]));
	msg = argv[3];


	signal((int)SIGSEGV, sigsegv);
	signal((int)SIGUSR1, sigusr1);
	signal((int)SIGUSR2, sigusr2);

	do {
		//Iniciar el receptor, escuchando en el puerto pasado como parámetro
		CMessageReceiver *cMsgRcv = new CMessageReceiver(port, netIf);
		cMsgRcv -> receiveMessage();
		sdrInfo_p = cMsgRcv -> getSenderInformation();
		printf("INFO DEL EMISOR, CON PUNTEROS: IP = %s, PORT = %d\n",
						inet_ntoa(sdrInfo_p -> sin_addr), ntohs(sdrInfo_p -> sin_port));
		portSdr = ntohs(sdrInfo_p -> sin_port);
		ipAddr = inet_ntoa(sdrInfo_p -> sin_addr);
		delete cMsgRcv;

		//Construir un emisor que envíe la respuesta.
		CMessageSender *cMsgSdr = new CMessageSender(ipAddr, portSdr, netIf);
		cMsgSdr -> sendMessage(msg, false);
		delete cMsgSdr;
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

