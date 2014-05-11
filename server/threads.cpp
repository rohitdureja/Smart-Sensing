#include "threads.h"

threads::threads(char *server_ip_l, int port)
	{	
		//strncpy(server_ip, server_ip_l,strlen(server_ip_l));
		conn.init_connect(server_ip_l, port, 1);
	}

void threads::send_message(frame* send_frame)
	{
		// Send message using tcp_connect.c/.h
		frame temp = *send_frame;
		this->send_frame_queue.push(temp);
	}

void threads::receive_message(frame & read_frame)
	{
		// Just pop from the queue if queue not empty
		unique_lock<mutex> receive_lk(this->receive_frame_queue_mtx);
		
		while(this->receive_frame_queue.empty())
		{
			this->receive_frame_cv.wait(receive_lk);
		}

		frame temp_frame = this->receive_frame_queue.front();
		this->receive_frame_queue.pop();
		this->receive_frame_queue_mtx.unlock();

		read_frame = temp_frame;
	}

void threads::sender()
	{
		frame send_frame;
		char send_buf[256];
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

			// send frame using tcp_connect.h and .c
			//while(sendto(csock, send_message.packet, strlen(send_message.packet), 0, (SA *) &send_message.address, sizeof(send_message.address)) < 0);
			send_frame.make(send_buf);
			this->conn.send_data(send_buf,send_frame.get_addr());
		}

	}
	
void threads::receiver()
	{
		frame read_frame;
		while(1)
		{
			// Receive messages using tcp_connect.h and tcp_connect.c 
			conn.receive_data(read_frame);
			this->receive_frame_queue.push(read_frame);
		}
	}
	