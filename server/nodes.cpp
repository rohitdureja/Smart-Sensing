#include "nodes.h"
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <signal.h>

map<int,Sensor> S_map;
map<int,Actuator> A_map;

int extract_key(string ip){

	istringstream iss(ip);
	string token;
	string ip_t[4];
	int i = 0;
	while (getline(iss, token, '.'))
	{
		ip_t[i] = token;
		i++;
	}
	// how to validate that the ip is indeed of our subnet
	return (atoi(ip_t[3].c_str()));
}

Actuator::Actuator(string ip_in){
	
	ip = ip_in;
	status = false;
	key = extract_key(ip);

	//setting up the timer
	sigemptyset(&timeup.sa_mask);
	timeup.sa_handler = TimerHandler;
	// set up sigaction to catch signal
	if (sigaction(key, &timeup, NULL) == -1) {
		perror("sigaction failed");
		exit(EXIT_FAILURE);
	}
	A_map[key]=*this;
}

void Actuator::set_status(int time_out){
	status = true;
	tid = SetTimer(time_out);
	event_time = time(NULL);
}

void Actuator::reset(){
	//some time checking mechanism has to be here
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

string Actuator::get_ip(){
	return ip;
}

void Actuator::TimerHandler(int signo){
	A_map[signo].reset();
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


Sensor::Sensor(string ip_in){
	ip = ip_in;
	key = extract_key(ip);
	S_map[key] = *this;
}

void Sensor::set_self(){

	//if its actuator is already set by a neighbour node just increase the time_out to 5
	//else set the neighbours as this is the node through which intersection is entered

	if(A_map[act_key].get_status()){
		if (A_map[act_key].get_time()<=60)
			A_map[act_key].set_status(300);
		else set_N(60);
	}
	else set_N(60);
}

void Sensor::set_N(int time){
	if (N_keys.empty())
		return;
	list<int>::iterator i;
	for (i = N_keys.begin(); i != N_keys.end(); ++i){
		A_map[S_map[*i].get_act()].set_status(time);
	}
}

int Sensor::get_key(){
	return key;
}

int Sensor::get_act(){
	return act_key;
}

string Sensor::get_ip(){
	return ip;
}

void Sensor::add_N(int n_key){
	N_keys.push_back(n_key);
}

void Sensor::add_act(int a_key){
	act_key = a_key;
}
