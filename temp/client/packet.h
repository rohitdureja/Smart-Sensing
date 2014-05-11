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

class frame
{
	struct sockaddr_in address;
	int ntype;
	int mtype;
	int payload;
public:
	frame(){};
	frame(int,int,int,struct sockaddr_in);

	void msg_set(int,int,int, struct sockaddr_in);
	void make(char *);
	void parse(char *, struct sockaddr_in);

	int get_ntype();
	int get_mtype();
	int get_payload();
	struct sockaddr_in get_addr();
};

#endif
