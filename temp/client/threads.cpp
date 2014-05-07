#include "threads.h"

class threads
{
public:
	void worker(queue * receive_queue, int * csock)
	{
	// Variables for each read message
	message_information read_message;
	app_packet *read_packet;
	struct sockaddr_in read_node_address;
	char read_servip[20];
	char read_port[20];
	char read_nodename[NAMELEN];

	// Variables for sending message
	message_information send_message;
	char send_raw_packet[BUFLEN];
	app_packet *send_packet = (app_packet *)send_raw_packet;
	struct sockaddr_in send_node_address;
	char send_servip[20];
	char send_port[20];	
	char send_nodename[NAMELEN];
	
	while(1)
	{
		unique_lock<mutex> receive_lk(receive_message_queue_mtx);
		while(*receive_queue->empty())
		{
			receive_message_cv.wait(receive_lk);
		}
		read_message = *receive_queue->front();
		*receive_queue->pop();
		receive_lk.unlock();
		read_packet = (struct app_packet *) read_message.packet;

		switch(read_packet->mtype)
		{
			case 1:
					break;

			case 2: 
					break;

			case 3:
					break;

			case 4: 
					break;
			..
			..
			..
			..
		}
	}
	}

	void sender(queue * send_queue, int *csock)
	{

		message_information send_message;
		char send_raw_packet[BUFLEN];
		app_packet *send_packet;
		send_packet = (struct app_packet *)send_message.packet;

		while(1)
		{
			memset(send_raw_packet, 0, BUFLEN);
			unique_lock<mutex> send_lk_send(send_message_queue_mtx);

			while(*send_queue->empty())
			{
				send_message_cv.wait(send_lk_send);
			}

			send_message = *send_queue->front();
			*send_queue->pop();
			send_lk_send.unlock();

			while(sendto(csock, send_message.packet, strlen(send_message.packet), 0, (SA *) &send_message.address, sizeof(send_message.address)) < 0);

			// Add Acknowledgement
		}
	}
	
	void receiver(queue * receive_queue, int *csock)
	{
		int n;
		struct sockaddr_in nodeaddr;
		socklen_t len;
		len = sizeof(nodeaddr);
		char mesg[BUFLEN];

		while(1)
		{
			n = recvfrom(*csock, mesg, BUFLEN, 0, (SA *)&nodeaddr, &len);
			...
			...
			receive_message_queue_mtx.lock();
			*receive_queue->push(...);
			receive_message_queue_mtx.unlock();
			receive_message_cv.notify_all();
			memset(mesg, 0, BUFLEN);
			...
		}
	}	

	void actuator_action()
	{

	}

	void person_detect()
	{

	}
	
};