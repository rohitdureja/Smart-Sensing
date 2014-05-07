

#ifndef PACKET_H_
#define PACKET_H_

#include <cstring>

using namespace std;

class frame
{
public:
	//frame();
	//frame(const frame &);
	void make(char *, int,  int,  int);
	void parse(char *, int *, int *, int *);
	void operator = (const frame &);
	// ~frame();

};


#endif