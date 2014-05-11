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

#include "threads.h"

#define MAX_NODES 100

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
	// constructor
	Actuator(){};

	// parametrised constructor to store actuator info in map
	Actuator(struct sockaddr_in addr);

	// sends timeout to the actuator nodes and init timer
	void set_status(int time_out);

	// called by signal handler to reset status
	void reset();

	// returns status
	bool get_status();

	// returns time left in timeout.
	double get_time();

	// returns address of the node
	struct sockaddr_in get_addr();

	// timeout handler
	static void TimerHandler(int);

	// set timer (countdown)
	timer_t SetTimer(int);
};

class Sensor {
	int key;
	struct sockaddr_in address;
	list<int> neighbour_keys; //Keys of the neighbouring nodes
	int act_key; //key of the actuator where the actuator is stored

	// set neighbors of the sensor. used by set_self().
	void set_neighbours(int time_out);
public:
	// constructor
	Sensor(){};

	// parametrised constructor
	Sensor(struct sockaddr_in addr);

	// sets it own actuator or neighboring actuator
	void set_self();
	
	// returns the key
	int get_key();

	// returns key of the actuator linkedin
	int get_act();

	// returns the address
	struct sockaddr_in get_addr();

	// adds neighboring sensor key in the list
	void add_neighbour(int n_key);

	// add actuator key to be linked to the sensor
	void add_act(int a_key);
};

class Server_Main {

public:
	// maps to hold sensor and actuator information
	map<int,Sensor> S_map;
	map<int,Actuator> A_map;
	
	threads th1("127.0.0.1", 10001,1); //mode server

	// constructor to bind
	Server_Main(){};

	// function to map sensor actuator network
	void set_localize();

	// start discovering network
	void network_discovery();

	// start service to listen to person activity
	void start_service();
};

#endif
