#ifndef TCP_CLIENT_H
# define TCP_CLIENT_H

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

class tcp_client
{
public:
	tcp_client();
	int connect_to_server(char *, int port);
	int send_data(frame *, struct sockaddr_in);
	int receive_data(char *);
	void conn_close();
	struct sockaddr_in get_server_addr();
private: 
	sockaddr_in server;
	int csock;
};


#endif 