// client.cpp file to be included in main.cpp

#include "tcp_connect.h"

//----------------------------------------------------------------------------------------//

tcp_connect::tcp_connect()
{
	this->csock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->csock < 0)
	{
		perror("Socket couldn't be created");
		exit(0);
	}


}

int tcp_connect::init_connect(char * ipaddr, int port, int mode)
{
	server.sin_addr.s_addr = inet_addr(ipaddr);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;

	if (mode==1) // mode is server 
	{
		bind(csock, (struct sockaddress *)&server, sizeof(server));
	}

	else // mode is client
	{
		if (connect(this->csock, (struct sockaddr *)&server, sizeof(server)) < 0)
		{
			perror("Couldn't establish connection to the server ");
			exit(0);
		}
	}


	return csock;
}

int tcp_connect::send_data(char * buf,struct sockaddr_in addr)
{
	return sendto(this->csock, buf, BUFLEN, 0, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
}

int tcp_connect::receive_data(frame &f)
{	
	char buf[256];
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(struct sockaddr_in);
	recvfrom(this->csock, buf, BUFLEN, 0, (struct sockaddr *) &(client_addr), &len);
	f.parse(buf,client_addr);
}

void tcp_connect::conn_close()
{
	close(this->csock);
}

struct sockaddr_in tcp_connect::get_server_addr()
{
	return this->server;
}