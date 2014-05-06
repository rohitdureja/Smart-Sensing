#ifndef NODES_H_
#define NODES_H_

#include <string>
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
#include <mutex>
#include <condition_variable>


using namespace std;

int extract_key(struct sockaddr_in addr);

/*
class node{
	
	string ip;
	int key;
*/

class Actuator {
	
	struct sockaddr_in address;
	int key;
	bool status;
	timer_t tid;
	time_t event_time;
	struct sigaction timeup;

public:
	Actuator(){};
	Actuator(struct sockaddr_in addr);

	void set_status(int time_out);
	void reset();
	bool get_status();
	double get_time();
//	string get_ip();

	static void TimerHandler(int);
	timer_t SetTimer(int);
};

class Sensor {
	int key;
	struct sockaddr_in address;
	list<int> N_keys; //Keys of the neighbouring nodes
	int act_key; //key of the actuator where the actuator is stored

public:
	Sensor(){};
	Sensor(sockaddr_in addr);

	void set_self();
	void set_N(int time);
	int get_key();
	int get_act();
//	string get_ip();
	void add_N(int n_key);
	void add_act(int a_key);
};

/*

class server_main {
	list<int> sensor_keys;
	list<int> actuator_keys;
public:
	void localize();
*/
#endif
