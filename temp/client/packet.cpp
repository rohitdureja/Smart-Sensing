#include "packet.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>


frame::frame(int Ntype, int Mtype, int Payload, struct sockaddr_in addr)
{
	this->ntype = Ntype;
	this->mtype = Mtype;
	this->payload = Payload;
	this->address = addr;
}

void frame::msg_set(int Ntype, int Mtype, int Payload,struct sockaddr_in addr)
{
	ntype = Ntype;
	mtype = Mtype;
	payload = Payload;
	address = addr;
}

void frame::make(char *buf)
{	
	sprintf(buf, "%d:%d:%d",ntype, mtype, payload);
}

void frame::parse(char *buf)
{
	ntype = atoi(strtok(buf, ":"));
	mtype = atoi(strtok(NULL, ":"));
	payload = atoi(strtok(NULL, ":"));
}

int frame::get_ntype()
{
	return this->ntype;
}

int frame::get_mtype()
{
	return this->mtype;
} 

int frame::get_payload()
{
	return this->payload;
}

struct sockaddr_in frame::get_addr()
{
	return this->address;
}