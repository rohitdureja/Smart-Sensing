#ifndef THREADS_H_
#define THREADS_H_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "tcp_client.h"
#include "message.h"
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include "packet.h"

using namespace std;

class threads
{

int csock;
queue<message_info> send_frame_queue;
mutex send_frame_queue_mtx;
condition_variable send_frame_cv;
queue<message_info> receive_frame_queue;
mutex receive_frame_queue_mtx;
condition_variable receive_frame_cv;

char * server_ip;
int server_port;

public:
	threads(char *, int);

	void sender();
	
	void receiver();

	void send_message(frame *);

	void receive_message(frame *);

/*	void actuator_action();

	void person_detect();
	*/
};

#endif