#ifndef NODES_H_
#define NODES_H_

#define _(x)

#include <queue>
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


using namespace std;

int extract_key(struct sockaddr_in addr);

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
	struct sockaddr_in get_addr();

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
	struct sockaddr_in get_addr();
	void add_N(int n_key);
	void add_act(int a_key);
};

class Server_Main {
public:
	map<int,Sensor> S_map;
	map<int,Actuator> A_map;
	
	queue<frame> send_queue;
	queue<frame> recv_queue;

	
	Server_Main(){};
	void set_localize();
};

#endif
