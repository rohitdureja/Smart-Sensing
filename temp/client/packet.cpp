#include "packet.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>

void frame::make(char *buf,int control,int mode, int payload)
{	
	int length;
	sprintf(buf, "%d:%d:%d", control, mode, payload);
	cout << strlen(buf) << endl;
}


void frame::parse(char *buf, int * control, int *mode, int *payload)
{
	*control = atoi(strtok(buf, ":"));
	*mode = atoi(strtok(NULL, ":"));
	*payload = atoi(strtok(NULL, ":"));
}

