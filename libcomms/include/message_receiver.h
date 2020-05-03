/*
 * message_receiver.h
 *
 *  Created on: 23/05/2012
 *      Author: luisda
 *
 *  Clase que define un receptor de mensajes IP utilizando UDP.
 */

#ifndef MESSAGE_RECEIVER_H_
#define MESSAGE_RECEIVER_H_

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

#define MAXBUFLEN 100

class CMessageReceiver {
	private:
		char* m_Buffer;
		sockaddr_in m_MyAddr;
		sockaddr_in m_TheirAddr;
		int m_Socket;
	public:
		CMessageReceiver(word port);
		~CMessageReceiver();
		int receiveMessage(void);
		char* getReceivedMessage(void);
		sockaddr_in getSenderInfo (void);
		sockaddr_in* getSenderInformation(void);

};

#endif /* MESSAGE_RECEIVER_H_ */
