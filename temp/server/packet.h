#ifndef PACKET_H_
#define PACKET_H_

#include <cstring>

using namespace std;

class frame
{
	int ntype;
	int mtype;
	int payload;
public:
	frame(){};
	frame(int,int,int);

	void msg_set(int,int,int);
	void make(char *);
	void parse(char *);

	int get_ntype();
	int get_mtype();
	int get_payload();
};

#endif
