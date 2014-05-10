// client.cpp file to be included in main.cpp

#include "tcp_client.h"

//----------------------------------------------------------------------------------------//

tcp_client::tcp_client()
{
	csock = socket(AF_INET, SOCK_STREAM, 0);
	if (csock < 0)
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

	if (connect(csock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("Couldn't establish connection to the server ");
		exit(0);
	}

	return csock;
}

int tcp_client::send_data(const char * packet, int length)
{
	return (send(csock, packet, length, 0));
}

int tcp_client::receive_data(char * buf)
{
	recv(csock, buf, 9, 0);
}

void tcp_client::conn_close()
{
	close(csock);
}