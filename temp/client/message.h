#ifndef MESSAGE_H_
#define MESSAGE_H_

#ifndef BUFLEN
#define BUFLEN 256
#endif

class message_info
{
public:
	struct sockaddr_in address;
	char packet[BUFLEN];
};

#endif