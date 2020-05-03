/*
 * testSend.cpp
 *
 *  Created on: 27/05/2012
 *      Author: luisda
 */

#include "include/message_sender.hpp"
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
	printf(" Usage: ./testSend <Net_Interface> <IP_address> <Port_number> <Message_to_send> [<Continuous(0=false, other=true)>] [<delay(ms)>]\n");
	printf("\n");
}

int main (int argc, char* argv[]) {
	int delay;
	char* ipAddr;
	char* msg;
	char* netIf;
	word port;
	g_undefined_loop = false;

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

	CMessageSender *cMsgSdr = new CMessageSender(ipAddr, port, netIf);

	do {
		cMsgSdr -> sendMessage(msg, false);
		usleep(1000*delay);
	} while (g_undefined_loop);

	delete cMsgSdr;
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
