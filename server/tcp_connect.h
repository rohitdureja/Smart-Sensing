#ifndef tcp_connect_H
# define tcp_connect_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include "packet.h"
//----------------------------------------------------------------------------------------//

using namespace std;

class tcp_connect
{
public:
	tcp_connect();
	int init_connect(char *, int port, int);
	int send_data(frame *, struct sockaddr_in);
	int receive_data(frame &);
	void conn_close();
	struct sockaddr_in get_server_addr();
private: 
	sockaddr_in server;
	int csock;
};


#endif 