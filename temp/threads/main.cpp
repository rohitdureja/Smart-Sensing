
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
#include "threads.h"
#include <thread>
#define BUFLEN 256

using namespace std;

int main(int argc, char *argv[])
{	
	threads th1, th2, th3, th4, th5;
	
	thread t1(&threads::worker, &th1);
	t1.join();

	thread t2(&threads::sender, &th2);
	t2.join();

	thread t3(&threads::receiver, &th3);
	t3.join();

	thread t4(&threads::person_detect, &th4);
	t4.join();
	
	thread t5(&threads::actuator_action, &th5);
	t5.join();	
	
}
