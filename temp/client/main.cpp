
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <queue>
#include "tcp_client.h"
#include "packet.h"
include "threads.h"
#define BUFLEN 256

extern queue<string> send_message_queue;
extern mutex send_message_queue_mtx;
extern queue<string> receive_message_queue;
extern mutex receive_message_queue_mtx;
extern condition_variable receive_message_cv;

class message_info
{
public:
	struct sockaddr_in address;
	char packet[BUFLEN];
};

class app_packet
{
public:
	uint8_t mtype;
	char payload[BUFLEN];
};


int main(int argc, char *argv[])
{
	if(argc<6)
	{
		cout << "not enough arguments!";
		cout << "correct usage: " << argv[0] << " <server_ip> <server_port> <mode> <group_id> <node_id>";
		exit(0);
	}

	// nodes next ot each other have the same group_id but different node_id.
	// the pair (group_id, node_id) uniquely identifies a node location
	// mode can be sensor or actuator
	int group_id = atoi(argv[4]);
	int node_id = atoi(argv[5]);
	int mode = atoi(argv[3]);

	int sockfd;

	// establish tcp connection to server
	tcp_client t1;
	sockfd = t1.connect_to_server(argv[1], atoi(argv[2]));

	threads th1, th2, th3, th4, th5;
	
	thread t1(&threads::worker, &th1, &receive_message_queue, &sockfd);
	t1.join();

	thread t2(&threads::sender, &th2, &send_message_queue, &sockfd);
	t2.join();

	thread t3(&threads::receiver, &th3, &receive_message_queue, &sockfd);
	t3.join();

	if(mode == SENSOR)
	{
		thread t4(&threads::person_detect, &th4);
		t4.join();
	}
	else if(mode == ACTUATOR)
	{
		thread t5(&threads::actuator_action, &th5);
		t5.join();	
	}


	tcp_client t1;
	csock = t1.connect_to_server("127.0.0.1", 10059);

}
