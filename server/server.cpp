#include "nodes.h"
#include "threads.h"

#include <string>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

extern Server_Main Server;

using namespace std;

int main()
{
	thread t1(&threads::sender, &Server.th1);
	t1.join();
	thread t2(&threads::receiver, &Server.th1);
	t2.join();

	//starting with discovery of nodes in the network
	Server.network_discovery();

	//giving commands to clients to localize in a set manner to get their respective neighbours
	Server.set_localize();

	//receive client messages containing neighbour keys and sesnor activity and actuator assigning
	Server.start_service();
	
	return 0;
}
