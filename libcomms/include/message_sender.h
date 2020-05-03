/*
 * message_sender.h
 *
 *  Created on: 13/05/2012
 *      Author: luisda
 */

#ifndef MESSAGE_SENDER_H_
#define MESSAGE_SENDER_H_

#include "../../common/include/general_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class CMessageSender {
	private:
		int m_Socket;
		sockaddr_in m_TheirAddr;
		hostent *m_HostEnt_p;
	public:
		CMessageSender(char* ipAddress, word port);
		~CMessageSender();
		int sendMessage(char* msgToSend, bool confirm);

};

#endif /* MESSAGE_SENDER_H_ */
