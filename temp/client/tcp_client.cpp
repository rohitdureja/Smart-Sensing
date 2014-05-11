// client.cpp file to be included in main.cpp

#include "tcp_client.h"

//----------------------------------------------------------------------------------------//

tcp_client::tcp_client()
{
	this->csock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->csock < 0)
	{
		perror("Socket couldn't be created");
		exit(0);
	}


}

int tcp_client::connect_to_server(char * ipaddr, int port)
{
	server.sin_addr.s_addr = inet_addr(ipaddr);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;

	if (connect(this->csock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("Couldn't establish connection to the server ");
		exit(0);
	}

	return csock;
}

int tcp_client::send_data(frame * send_frame, struct sockaddr_in send_address)
{
	return sendto(this->csock, send_frame, BUFLEN, 0, (struct sockaddr *) &send_address, sizeof(send_address));
}

int tcp_client::receive_data(char * buf)
{	
	socklen_t len = sizeof(this->server);
	recvfrom(this->csock, buf, BUFLEN, 0, (struct sockaddr *) &(this->server), &len);
}

void tcp_client::conn_close()
{
	close(this->csock);
}

struct sockaddr_in tcp_client::get_server_addr()
{
	return this->server;
}