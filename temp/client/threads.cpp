#include "threads.h"

// Constructor, Connect to Server 
threads::threads(char *server_ip_l, int port)
{	
	this->conn.connect_to_server(server_ip_l, port, 0);
}

// Push frame onto the send queue
void threads::send_message(frame* send_frame)
{
	frame f = *send_frame;
	this->send_frame_queue.push(f);
}

// Get frame by popping the receive queue
void threads::receive_message(frame& read_frame)
{
	frame temp_frame = this->receive_frame_queue.front();
	this->receive_frame_queue.pop();
	read_frame = temp_frame;
}

// Thread function to send frames from the send queue
void threads::sender()
{
	frame send_frame;
	char * send_buf;
	while(1)
	{	
		// Create unique lock on the send queue mutex
		unique_lock<mutex> send_lk_send(this->send_frame_queue_mtx);
		
		while(this->send_frame_queue.empty())
		{
			// Conditional variable wait 
			send_frame_cv.wait(send_lk_send);	
		}	

	send_frame = this->send_frame_queue.front();
	send_frame_queue.pop();
	send_lk_send.unlock();

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
		conn.receive_data(receive_buf);
		read_frame.parse(receive_buf, this->conn.get_server_addr());
		this->receive_frame_queue.push(read_frame);
	}
}	

void threads::worker()
{	
	frame read_frame;
	unique_lock<mutex> receive_lk(this->receive_frame_queue_mtx);
		
	while(this->receive_frame_queue.empty())
	{
		this->receive_frame_cv.wait(receive_lk);
	}

	read_frame = this->receive_frame_queue.front();
	this->receive_frame_queue.pop();
	this->receive_frame_queue_mtx.unlock();
		
	// do things based on what the frame has

	
}