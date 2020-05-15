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
	printf(" Uso: ./enviar_comando <Net_Interface> <IP_address> <Port_number> <comando> <num_valvula>\n");
	printf("\n");
	printf("       <comando> puede ser 'a' (activar válvula) o 'd' (desactivar válvula)");
	printf("       <num_valvula> es el número de la válvula a activar/desactivar (la válvula maestra es la 5)");
	printf("\n");
}

int main (int argc, char* argv[]) {
	int delay;
	char* ipAddr;
	char* msg = new char[3];
	char* netIf;
	word port;
	word portRcv;
	
	char* str_comando = argv[4];
	char comando = str_comando[0];
	int num_valv = atoi(argv[5]);

	g_undefined_loop = false;
	sockaddr_in* sdrInfo_p = NULL;

	printf("Número de argumentos: %i\n", argc);

	if (argc != 6) {
		show_help();
		exit(1);
	} 

	netIf = argv[1];
	ipAddr = argv[2];
	port = (word)(atoi(argv[3]));
	//msg = argv[4];
	memset(msg, 0x00, sizeof(msg));

	//Construimos el mensaje: primer byte, 'a' o 'd', segundo byte, ID de válvula
	msg[0] = comando;
	msg[1] = num_valv;

	signal((int)SIGSEGV, sigsegv);
	signal((int)SIGUSR1, sigusr1);
	signal((int)SIGUSR2, sigusr2);
	signal((int)SIGINT, sigint);
	

	//do {

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
		usleep(1000000);
		//usleep(1000*delay);
	//} while (g_undefined_loop);

	///delete cMsgSdr;

}

void sigsegv(int sig) {
	printf ("Petose...\n");
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
