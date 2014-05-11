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

using namespace std;

int main(int argc, char *argv[])
{
	// Create object and initialise connection to send init message
	threads th1(argv[1], atoi(argv[2]), atoi(argv[3]));

	// Start the sender thread
	thread t1(&threads::sender, &th1);

	// join to the main thread
	t1.join();

	// Start the receive thread
	thread t2(&threads::receiver, &th1);
		
	// join to the receive threads
	t2.join();

	// start the worker thread
	thread t3(&threads::worker, &th1);

	//joining to the worker thread
	t3.join();

	if(atoi(argv[3])==1) //detect if the nodetype is sensor
	{
		thread t4(&threads::sensing,&th1);
		t4.join();
	}
}
