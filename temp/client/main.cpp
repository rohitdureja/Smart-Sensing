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
#include "packet.h"
#include "threads.h"
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>

#include 


int main(int argc, char *argv[])
{
	// Create object and initialise connection to send init message
	threads th1(argv[1], atoi(argv[2]));

	// Start the sender thread
	thread t2(&threads::sender, &th1);

	// join to the main thread
	t2.join();

	// Start the receive thread
	thread t3(&threads::receiver, &th1);
		
	// join to the receive threads
	t3.join();

	// Infinite loop for parsing messages

	// Init: received messages
	frame read_frame;
	
	// Init: send messages
	frame send_frame;
	
/*	// Receive Message from the Queue
	th1.receive_message(&read_frame);

	// Sending message
	th1.send_message(&send_frame);
*/

	// Deal with converting message to frame also!! 

	while(1)
	{
		unique_lock<mutex> receive_lk(th1.get_receive_frame_queue_mtx());
		
		while(th1.get_receive_frame_queue.empty())
		{
			th1.receive_frame_cv.wait(receive_lk);
		}

		read_frame = th1.get_receive_frame_queue.front();
		receive_message_queue.pop();
		receive_message_queue_mtx.unlock();
		read_packet = (struct app_packet *)read_message.packet;


	}

}
