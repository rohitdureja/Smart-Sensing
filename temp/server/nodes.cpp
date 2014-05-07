#include "nodes.h"

#include <cstring>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define _(x) 


Server_Main Server;

int extract_key(struct sockaddr_in addr){

	char *ip = inet_ntoa(addr.sin_addr);
	int port = ntohs(addr.sin_port);
	
	char *k;
	k = strtok(ip,".");
	for(int i=0;i<3;++i)         //To obtain the last part of the IPV4 address
		k = strtok(NULL,".");
	return (atoi(k)+port);		//Unique key for the sensor and the actuator
}

Actuator::Actuator(struct sockaddr_in addr){
	_(requires \addr is unique)
	
	address = addr;
	status = false;
	key = extract_key(address);
	//setting up the timer
	sigemptyset(&timeup.sa_mask);
	timeup.sa_handler = TimerHandler;
	// set up sigaction to catch signal
	if (sigaction(key, &timeup, NULL) == -1) {
		perror("sigaction failed");
		exit(EXIT_FAILURE);
	}
	Server.A_keys.push_back(key);
	Server.A_map[key]=*this;				//Adding the actuator to the map
	_(requires \Server.A_map[key] is unoccupied before writing)
}

void Actuator::set_status(int time_out){
	status = true;
	tid = SetTimer(time_out);
	event_time = time(NULL);
}

void Actuator::reset(){
	status = false;
}

bool Actuator::get_status(){
	return status;
}

double Actuator::get_time(){
	if (status)
		return (difftime(time(NULL), event_time));
	return 0;
}

struct sockaddr_in Actuator::get_addr(){
	return address;
}

void Actuator::TimerHandler(int signo){
	Server.A_map[signo].reset();
}

timer_t Actuator::SetTimer(int time_out){

	static struct sigevent sigev;
	static timer_t tid;
	static struct itimerspec itval;
	static struct itimerspec oitval;
	int signo = key;
	// Create the POSIX timer to generate signo
	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = signo;
	sigev.sigev_value.sival_ptr = &tid;

	if (timer_create(CLOCK_REALTIME, &sigev, &tid) == 0) {
		itval.it_value.tv_sec = time_out;
		itval.it_value.tv_nsec = 0;

		itval.it_interval.tv_sec = 0;
		itval.it_interval.tv_nsec = 0;

		if (timer_settime(tid, 0, &itval, &oitval) != 0) {
			perror("time_settime error!");
		}
	}
	else {
		perror("timer_create error!");
		return NULL;
	}
	return tid;
}


Sensor::Sensor(struct sockaddr_in addr){
	address = addr;
	key = extract_key(address);
									//adding the sensor in the map
	Server.S_keys.push_back(key);
	Server.S_map[key] = *this;
}

void Sensor::set_self(){

	/*If a sensor detects a person (entering the intersection), the server sets a time limit of 60 seconds on the sensor's neighbour's actuators .
	When another sensor in the intersection detects a person again (leaving the intersection) it increases the time of  its already on actuator 
	to 300 seconds*/

	
	if(Server.A_map[act_key].get_status()){
		if (Server.A_map[act_key].get_time()<=60)
			Server.A_map[act_key].set_status(300);
		else set_N(60);
	}
	else set_N(60);
}

void Sensor::set_N(int time_out){
	if (N_keys.empty())
		return;
	list<int>::iterator i;
	for (i = N_keys.begin(); i != N_keys.end(); ++i){
		Server.A_map[Server.S_map[*i].get_act()].set_status(time_out);
	}
}

int Sensor::get_key(){
	return key;
}

int Sensor::get_act(){
	return act_key;
}

struct sockaddr_in Sensor::get_addr(){
	return address;
}

void Sensor::add_N(int n_key){
	N_keys.push_back(n_key);
}

void Sensor::add_act(int a_key){
	act_key = a_key;
}


void Server_Main::set_localize(){

}
