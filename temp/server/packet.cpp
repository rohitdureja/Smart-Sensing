#include "packet.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>

frame::frame(int Ntype, int Mtype, int Payload)
{
	ntype = Ntype;
	mtype = Mtype;
	payload = Payload;
}

void frame::msg_set(int Ntype, int Mtype, int Payload)
{
	ntype = Ntype;
	mtype = Mtype;
	payload = Payload;
}

void frame::make(char *buf)
{	
	sprintf(buf, "%d:%d:%d",ntype, mtype, payload);
//	cout << strlen(buf) << endl;
}

void frame::parse(char *buf)
{
	ntype = atoi(strtok(buf, ":"));
	mtype = atoi(strtok(NULL, ":"));
	payload = atoi(strtok(NULL, ":"));
}

int get_ntype()
{
	return ntype;
}

int get_mtype()
{
	return mtype;
} 

int get_payload()
{
	return payload;
}

