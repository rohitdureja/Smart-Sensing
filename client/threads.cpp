#include "threads.h"

// Constructor, Connect to Server 
threads::threads(char *server_ip_l, int port, int nodetype)
{	
	this->nodetype = nodetype;
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
	
	//sending type of node to server to get registered
	frame read_frame(nodetype,1,0,0);
	this->send_message(&read_frame);

	while(1){

		unique_lock<mutex> receive_lk(this->receive_frame_queue_mtx);
		
		while(this->receive_frame_queue.empty())
		{
			this->receive_frame_cv.wait(receive_lk);
		}

		read_frame = this->receive_frame_queue.front();
		this->receive_frame_queue.pop();
		this->receive_frame_queue_mtx.unlock();
	
		switch(read_frame.get_mtype())
		{
			case 1: //receiving acknowledgement from server that the node is registered
					//getting key from server to be used in Localization
					break;

			case 2: //Transmitter mode: receiving keys of all other nodes for localization 
					break;

			case 3: //Receiver mode: receiving key of the node currently in transmitting node
					break;

			case 4: //Server message informing that Localization complete
					//Server orders to send acquired node keys during Localization
					break;

			case 5: //Received only if nodetype==Actuator
					//get time_out to pass on to hardware actuator setting auto reset
					break;
		}	
	}
}

void threads::sensing(){
	//detects sensor activity on the hardware to pass on to server
}