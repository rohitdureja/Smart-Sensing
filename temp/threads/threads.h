#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

class threads
{
public:
	void worker();

	void sender();
	
	void receiver();

	void actuator_action();

	void person_detect();
	
};