#include "threads.h"


	/*void worker(queue * receive_queue, int * csock)
	{

	}*/

	threads::threads(char *server_ip_l, int port)
	{	
		//strncpy(server_ip, server_ip_l,strlen(server_ip_l));
		conn.connect_to_server(server_ip_l, port);
	}

void threads::send_message(frame* send_frame)
	{
		// Send message using tcp_client.c/.h
	}

void threads::receive_message(frame* read_frame)
	{
		// Receive message using tcp_client.c/.h
	}

void threads::sender()
	{
		frame send_frame;
		char * send_buf;
		while(1)
		{
			unique_lock<mutex> send_lk_send(this->send_frame_queue_mtx);
			
			while(this->send_frame_queue.empty())
			{
				send_frame_cv.wait(send_lk_send);	
			}	

			send_frame = this->send_frame_queue.front();
			send_frame_queue.pop();
			send_lk_send.unlock();

			// send frame using tcp_client.h and .c
			//while(sendto(csock, send_message.packet, strlen(send_message.packet), 0, (SA *) &send_message.address, sizeof(send_message.address)) < 0);
			send_frame.make(send_buf);
			this->conn.send_data(&send_frame, send_frame.get_addr());
		}

	}
	
void threads::receiver()
	{
		frame read_frame;
		char * receive_buf;
		while(1)
		{
			// Receive messages using tcp_client.h and tcp_client.c 
			conn.receive_data(receive_buf);
			read_frame.parse(receive_buf, this->conn.get_server_addr());
			this->receive_frame_queue.push(read_frame);

		}
	}	