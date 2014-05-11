#ifndef BUFLEN
#define BUFLEN 256
#endif	

#ifndef PACKET_H_
#define PACKET_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

//class frame for the type of message to be sent and received
class frame
{
	struct sockaddr_in address;
	int ntype;
	int mtype;
	int payload;
public:

	frame(){};
	
//constructor to set packet info
	frame(int,int,int,struct sockaddr_in);

//function to overwrite packet info
	void msg_set(int,int,int, struct sockaddr_in);

//function to make and store string message from packet info while sending
	void make(char *);

//function to get packet info from string message while receiving
	void parse(char *,struct sockaddr_in);

//accessor funcions
	int get_ntype();
	int get_mtype();
	int get_payload();
	struct sockaddr_in get_addr();
};

#endif
