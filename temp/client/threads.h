#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

queue<string> send_message_queue;
mutex send_message_queue_mtx;
queue<string> receive_message_queue;
mutex receive_message_queue_mtx;
condition_variable receive_message_cv;

class threads
{
public:
	void worker(queue * receive_queue, int * csock);

	void sender(queue * send_queue, int *csock);
	
	void receiver(queue * receive_queue, int *csock);

	void actuator_action();

	void person_detect();
	
};