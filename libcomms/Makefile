all:	testSend	testReceive	testMulticastServer	testMulticastClient	testNetworkIfManager	sendAndReceive

testNetworkIfManager:	network_interface_manager.o
	g++	-c	-g	testNetworkIfManager.cpp
	g++	-o	testNetworkIfManager	testNetworkIfManager.o	network_interface_manager.o

testSend:	message_sender.o	network_interface_manager.o
	g++	-c	-g	testSend.cpp
	g++	-o	testSend	testSend.o	message_sender.o	network_interface_manager.o

testReceive:	message_receiver.o	network_interface_manager.o
	g++	-c	-g	testReceive.cpp
	g++	-o	testReceive	testReceive.o	message_receiver.o	network_interface_manager.o
	
sendAndReceive:	message_sender.o	message_receiver.o	network_interface_manager.o
	g++	-c	-g	sendAndReceive.cpp
	g++	-o	sendAndReceive	sendAndReceive.o	message_sender.o	message_receiver.o	network_interface_manager.o
	
receiveAndReply:	message_sender.o	message_receiver.o	network_interface_manager.o
	g++	-c	-g	receiveAndReply.cpp
	g++	-o	receiveAndReply	receiveAndReply.o	message_sender.o	message_receiver.o	network_interface_manager.o	

testMulticastServer:	multicast_server.o
	g++	-c	-g	testMulticastServer.cpp
	g++	-o	testMulticastServer	testMulticastServer.o	multicast_server.o

testMulticastClient:	multicast_client.o	network_interface_manager.o
	g++	-c	-g	testMulticastClient.cpp
	g++	-o	testMulticastClient	testMulticastClient.o	multicast_client.o	network_interface_manager.o

network_interface_manager.o:
	g++	-c	-g	network_interface_manager.cpp

message_sender.o:
	g++	-c	-g	message_sender.cpp

message_receiver.o:	
	g++	-c	-g	message_receiver.cpp

multicast_server.o:
	g++	-c	-g	multicast_server.cpp

multicast_client.o:
	g++	-c	-g	multicast_client.cpp
	
libComms.so:
	g++ -c	-g	-fPIC	message_sender.cpp	-o	message_sender.o
	g++ -c	-g	-fPIC	message_receiver.cpp	-o	message_receiver.o
	g++ -c	-g	-fPIC	multicast_server.cpp	-o	multicast_server.o
	g++ -c	-g	-fPIC	multicast_client.cpp	-o	multicast_client.o
	g++	-c	-g	-fPIC	network_interface_manager.cpp	-o	network_interface_manager.o
	g++	network_interface_manager.o	message_sender.o	message_receiver.o	multicast_client.o	multicast_server.o	-shared -o libComms.so
	
ejecutables_sh: libComms.so	
	g++	-L.	-o	enviar_comando	enviarComando.cpp	-lComms
	g++	-L.	-o	testSend	testSend.cpp -lComms
	g++	-L.	-o	testReceive	testReceive.cpp -lComms
	g++	-L.	-o	testMulticastClient	testMulticastClient.cpp	-lComms
	g++	-L.	-o	testMulticastServer	testMulticastServer.cpp	-lComms
	g++	-L.	-o	sendAndReceive sendAndReceive.cpp	-lComms
	g++	-L.	-o	receiveAndReply	receiveAndReply.cpp	-lComms
	
clean:
	rm	-f	*.o *.so	testNetworkIfManager	testSend	testReceive	testMulticastServer	testMulticastClient	sendAndReceive	receiveAndReply	enviar_comando
