/*
 * testLibComms.cpp
 *
 *  Created on: 15/05/2012
 *      Author: luisda
 */

#include "include/message_sender.hpp"
//#include "include/message_receiver.h"

int main (int argc, char* argv[]) {
	char* ipAddr = "127.0.0.1";
	char* msg = "Mensaje de prueba";
	word port = 4950;
	CMessageSender *cMsgSdr = new CMessageSender(ipAddr, port);
	//CMessageReceiver *cMsgRcv = new CMessageReceiver(ipAddr, (port+1));

	for(int i = 0; i < 20; i++) {
		cMsgSdr -> sendMessage(msg, false);
		sleep(1);
	}

	delete cMsgSdr;
}
