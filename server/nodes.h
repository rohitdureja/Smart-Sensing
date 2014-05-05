#include<string>
#include<map>
#include<list>
#include<stdio.h>
#include<time.h>
#include<signal.h>

using namespace std;

int extract_key(string ip);

class Actuator {
	
	string ip;
	int key;
	bool status;
	static timer_t tid;
	time_t event_time;
	struct sigaction timeup;

public:
	Actuator(){};
	Actuator(string ip, map<int,Actuator> &act_map);

	void set_status(int time_out);
	void reset();
	bool get_status();
	double get_time();
	string get_ip();

	void TimerHandler(int);
	timer_t SetTimer(int);
};

class Sensor {
	int key;
	string ip;
	list<int> N_keys; //Keys of the neighbouring nodes
	int act_key; //key of the actuator where the actuator is stored

public:
	Sensor(){};
	Sensor(string ip_in, map<int, Sensor> &sensor_map);

	void set_self(map<int,Sensor> &sensor_map, map<int,Actuator> &act_map);
	void set_N(int time, map<int, Sensor> &sensor_map, map<int,Actuator> &act_map);
	int get_key();
	string get_ip();
	void add_N(int n_key);
	void add_act(int a_key);
};