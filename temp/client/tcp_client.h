
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


# define BUFLEN 256
//----------------------------------------------------------------------------------------//

using namespace std;

class tcp_client
{
public:
	tcp_client();
	int connect_to_server(const char *, int port);
	int send_data(const char *, int);
	int receive_data(char *);
	void conn_close();
	//virtual ~tcp_client();
private: 
	sockaddr_in server;
	int csock;
};


#endif 