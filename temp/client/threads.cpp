#include "threads.h"


	/*void worker(queue * receive_queue, int * csock)
	{

	}*/

	threads::threads(char *server_ip_l, int port)
	{
		strncpy(server_ip, server_ip_l,strlen(server_ip_l));

		this->csock = socket(AF_INET, SOCK_STREAM, 0);
		if (this->csock < 0)
		{
			perror("Socket couldn't be created");
			exit(0);
		}

	}

void threads::send_message(frame* send_frame)
	{

	}

void threads::receive_message(frame* read_frame)
	{

	}

void threads::sender()
	{
		while(1)
		{
			unique_lock<mutex> send_lk_send(this->send_frame_queue_mtx);
			
			while(this->send_frame_queue.empty())
			{
				send_frame_cv.wait(send_lk_send);
			}	

			send_frame = send_frame_queue.front();
			send_frame_queue.pop();
			send_lk_send.unlock();

			// send frame using tcp_client.h and .c
			//while(sendto(csock, send_message.packet, strlen(send_message.packet), 0, (SA *) &send_message.address, sizeof(send_message.address)) < 0);

		}

	}
	
void threads::receiver()
	{
/*		int n;
		struct sockaddr_in nodeaddr;
		socklen_t len;
		len = sizeof(nodeaddr);
		char mesg[BUFLEN];
*/
		while(1)
		{
			// Receive messages using tcp_client.h and tcp_client.c 
		}
	}	
